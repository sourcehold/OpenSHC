"""Generate "this read belongs at its point of use" variants of one function for quick_styles.py.

The decompiler lifts a field read to the top of the block it is used in; the original reads it where
it is used, and which side of an intervening call or test the read falls on changes the register
allocation of everything around it. Measured over Map::Units::TroopValueState this was the single
strongest source choice left: 27.7% -> 49.5% on `recountTotalTroopValue` (one read moved past a
call), 70.7% -> 100% on `queueOilThrowForIdleArchers` (past two threshold tests), 49.4% -> 61.5% on
`collectArcherUnitsByLocation` (into the branch that uses it).

For every single-line assignment whose variable is next mentioned further down, this writes a
variant with that statement moved to just before the use. Candidates whose right-hand side contains
a call are skipped: moving one of those changes evaluation order, not just allocation.

**Moving a read later crosses whatever sits between.** That is safe only if nothing in between
writes the field, so read `git diff` on the winner before keeping it - a call that happens to update
the same struct makes the variant wrong however well it scores.

usage: move_read.py FILE.cpp [--run] [--max N]
"""

import re
import subprocess
import sys

import common

ASSIGN = re.compile(r"^(\s+)([A-Za-z_]\w*) = ([^;]+);$")
DECL = re.compile(r"^(\s+)(?:[A-Za-z_][\w:]*\**\s+)([A-Za-z_]\w*) = ([^;]+);$")

args = [a for a in sys.argv[1:] if not a.startswith("--")]
if not args:
    sys.exit(__doc__)
limit = 12
if "--max" in sys.argv:
    limit = int(sys.argv[sys.argv.index("--max") + 1])
path = common.repo_relative(args[0])
text = common.read_text(path)
lines = text.split("\n")
name = re.search(r"//\s*FUNCTION:[^\n]*\n\s*[\w:&*\s]+?(\w+)\s*\(", text).group(1)

out_dir = common.TMP / "variants" / name
out_dir.mkdir(parents=True, exist_ok=True)
(out_dir / "base.cpp").write_text(text, encoding="utf-8", newline="")

depth, level = [], 0
for line in lines:
    opens, closes = line.count("{"), line.count("}")
    depth.append(level - closes if closes else level)
    level += opens - closes

made = 0
for i, line in enumerate(lines):
    m = ASSIGN.match(line) or DECL.match(line)
    if not m:
        continue
    indent, var, rhs = m.group(1), m.group(2), m.group(3)
    if "(" in rhs and "MACRO_CALL" in rhs:
        continue
    word = re.compile(r"\b%s\b" % re.escape(var))
    target = None
    for j in range(i + 1, len(lines)):
        if word.search(lines[j]):
            target = j
            break
    if target is None or target <= i + 1:
        continue
    # a second assignment to the same variable in between means the read is not the one in use
    if any(re.match(r"\s+%s = " % re.escape(var), lines[k]) for k in range(i + 1, target)):
        continue
    # the first mention assigning the variable means this statement is dead once moved there
    if re.match(r"\s+%s = " % re.escape(var), lines[target]):
        continue
    # never move a statement across a loop head (it would run a different number of times)
    if any(re.match(r"\s*(?:\} )?(?:do \{|while \(|for \()", lines[k]) for k in range(i + 1, target + 1)):
        continue
    # and never move it out of its enclosing block: only deeper or level, never shallower
    if depth[target] < depth[i]:
        continue
    moved = list(lines)
    stmt = moved.pop(i)
    use_indent = re.match(r"\s*", moved[target - 1]).group(0)
    moved.insert(target - 1, use_indent + stmt.strip())
    style = "move_%s_%d" % (re.sub(r"\W", "", var)[:16], i + 1)
    (out_dir / (style + ".cpp")).write_text("\n".join(moved), encoding="utf-8", newline="")
    made += 1
    if made >= limit:
        break

print("%s: %d variant(s) in %s" % (name, made, out_dir))
if "--run" in sys.argv and made:
    subprocess.run([sys.executable, str(common.ROOT / "tools/reimplementation-helper/batch/quick_styles.py"), name])

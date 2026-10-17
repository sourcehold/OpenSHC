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

It refuses to move a statement across a loop head, out of its enclosing block, past a `goto` or a
label, next to a use that assigns the variable, or into a block some later use sits outside of.
Each of those produced a *winning* variant that was wrong before the guard existed: a counter reset
inside its own loop, a pointer increment lifted out of its walk, a unit scan restarted per queue
entry, and a `switch` arm left reading an uninitialised local while the other arms read it too. One
of them won by 0.09 points, so the score is no protection.

**What remains unguarded is aliasing**: moving a read later still crosses whatever sits between, and
that is only safe if nothing in between writes the field. Read `git diff` on the winner and check
the callees it now crosses before keeping it.

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
    # a goto or a label in between means the statement may be re-entered or skipped
    if any(re.search(r"goto|^\s*\w*LAB_\w+:", lines[k]) for k in range(i + 1, target + 1)):
        continue
    # every later use has to live inside the block we are moving into, or the other uses would
    # read the variable before this statement runs - moving `sVar3` into one switch arm left the
    # other arms reading it uninitialised
    block_end = next((k for k in range(target + 1, len(lines)) if depth[k] < depth[target]), len(lines))
    if any(word.search(lines[k]) for k in range(block_end, len(lines))):
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

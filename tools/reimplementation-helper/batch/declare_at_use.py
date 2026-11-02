"""Move a function's leading declaration block down to each variable's first use.

The decompiler declares everything at the top; the original declared at first use. This
merges the declaration into the first assignment wherever the scope allows it, and drops
declarations that are never used at all.

Unlike a plain "single assignment" rule this also handles variables assigned more than
once: only the *first* assignment has to dominate every later use, which is checked by
tracking brace depth from that assignment to the last use. Anything it cannot prove is
left alone and reported, so the output doubles as a list of what still needs a hand.

Declaration position *does* change code generation, so measure after running this. MSVC
assigns stack slots in declaration order - see perm_decls.py - and moving a declaration
past another one moves both locals between slots, which usually moves them between
registers too. Three functions in Map/Units/TribesState turned on nothing else:
getMajorityArcherTypeEuropeanOrArabian 69.6% -> 88.2%, getTribeAliveStatus
68.6% -> 85.9% and updateTribeRallyFlags 74.7% -> 100%, all three just by declaring the
local that reads the tribe size after the zero-initialised counters instead of before
them. This docstring used to say the opposite; it was wrong.

usage:
  declare_at_use.py [path-filter]
"""

import re
import sys

import common

path_filter = sys.argv[1] if len(sys.argv) > 1 else ""

DECL = re.compile(r"^(?P<type>(?:unsigned\s+|const\s+)*[A-Za-z_][\w:]*)\s+"
                  r"(?P<ptr>\**)\s*(?P<name>[A-Za-z_]\w*)\s*"
                  r"(?P<arr>\[[^\]]*\])?\s*;$")


def code_of(line):
    return re.sub(r"//.*", "", line).rstrip()


def top_level_comma(code):
    depth = 0
    for ch in code:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif ch == "," and depth == 0:
            return True
    return False


def covers(lines, first, last):
    """True when the block opened at `first` is still open at `last`.

    Comparing brace depth per line is not enough: `} else if (...) {` closes one block
    and opens another at the same depth, so a use in the sibling arm reads as covered
    and the declaration moves out from under it ("C2065: undeclared identifier"). Scan
    characters instead and fail on any drop below the starting depth, mid-line included.
    """
    depth = 0
    for n in range(first, last + 1):
        for ch in code_of(lines[n]):
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth < 0:
                    return False
    return True


def is_statement(lines, n):
    """True only where a declaration may legally replace the assignment on line n.

    The decompiler folds assignments into conditions as comma expressions, and
    clang-format then wraps them so the assignment looks like a statement of its own:

        if (iVar2 == 0
            && (uVar3 = foo(),
                uVar3 < 5)) {

    Declaring there gives "C2275: illegal use of this type as an expression", which
    compiles nowhere but is easy to miss - so require a real statement boundary: the
    assignment has to be a balanced, semicolon-terminated line with no comma of its
    own, following a line that ends a statement or opens a block.
    """
    code = code_of(lines[n])
    if not code.endswith(";"):
        return False
    body = code[:-1]
    if body.count("(") != body.count(")") or body.count("{") != body.count("}"):
        return False
    if top_level_comma(body):
        return False                              # x = 1, y = 2;
    for k in range(n - 1, -1, -1):
        if lines[k].strip():
            prev = code_of(lines[k])
            return prev.endswith((";", "{", "}", ":"))
    return True                                   # first line of the body


def move(path):
    text = common.read_text(path).replace("\r\n", "\n")
    brace = re.compile(r"\n[ \t]*\{[ \t]*\n").search(text, text.index("// FUNCTION:"))
    if not brace:
        return None
    head, lines = text[:brace.end()], text[brace.end():].split("\n")

    decls, i = [], 0
    while i < len(lines):
        stripped = lines[i].strip()
        if not stripped:
            i += 1
            continue
        m = DECL.match(stripped)
        if not m:
            break
        decls.append((m.group("name"), m.group("type"), m.group("ptr") or "",
                      m.group("arr") or "", i))
        i += 1
    if not decls:
        return None

    drop, unsafe = set(), []
    for var, vtype, ptr, arr, decl_at in decls:
        word = re.compile(r"(?<![\w])%s(?![\w])" % re.escape(var))
        uses = [n for n in range(len(lines)) if n != decl_at and word.search(lines[n])]
        if not uses:
            drop.add(decl_at)                     # never used
            continue
        if arr:
            continue                              # arrays keep their declaration
        first = uses[0]
        if not re.match(r"^\s*%s\s*=[^=]" % re.escape(var), lines[first]):
            continue                              # first touch is not a plain assignment
        if not is_statement(lines, first):
            unsafe.append(var)                    # folded into a condition, not a statement
            continue
        if not covers(lines, first, uses[-1]):
            continue                              # the scope would not cover every use
        lines[first] = re.sub(r"^(\s*)%s\s*=" % re.escape(var),
                              lambda m: "%s%s %s%s =" % (m.group(1), vtype, ptr, var),
                              lines[first], count=1)
        drop.add(decl_at)

    if not drop:
        return None
    kept = [d[0] for d in decls if d[4] not in drop]
    common.write_text(path, head + "\n".join(l for n, l in enumerate(lines) if n not in drop))
    return len(decls), len(drop), kept, unsafe


touched = 0
for f in common.list_files():
    if path_filter not in f:
        continue
    result = move(f)
    if not result:
        continue
    count, moved, kept, unsafe = result
    common.format_file(f)
    touched += 1
    print("%-52s %2d declarations, %2d moved, left: %s%s"
          % (f.rsplit("/", 1)[-1][:-4], count, moved, " ".join(kept) or "-",
             ", in a condition: " + " ".join(unsafe) if unsafe else ""))
print("%d file(s) changed" % touched)

"""Move a function's leading declaration block down to each variable's first use.

The decompiler declares everything at the top; the original declared at first use. This
merges the declaration into the first assignment wherever the scope allows it, and drops
declarations that are never used at all.

Unlike a plain "single assignment" rule this also handles variables assigned more than
once: only the *first* assignment has to dominate every later use, which is checked by
tracking brace depth from that assignment to the last use. Anything it cannot prove is
left alone and reported, so the output doubles as a list of what still needs a hand.

Declaration position does not change code generation, so this is a readability pass; run
it before measuring, not instead of.

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


def depths(lines):
    out, d = [], 0
    for line in lines:
        out.append(d)
        code = re.sub(r"//.*", "", line)
        d += code.count("{") - code.count("}")
    return out


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

    drop = set()
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
        d = depths(lines)
        if any(d[n] < d[first] for n in range(first, uses[-1] + 1)):
            continue                              # the scope would not cover every use
        lines[first] = re.sub(r"^(\s*)%s\s*=" % re.escape(var),
                              lambda m: "%s%s %s%s =" % (m.group(1), vtype, ptr, var),
                              lines[first], count=1)
        drop.add(decl_at)

    if not drop:
        return None
    kept = [d[0] for d in decls if d[4] not in drop]
    common.write_text(path, head + "\n".join(l for n, l in enumerate(lines) if n not in drop))
    return len(decls), len(drop), kept


touched = 0
for f in common.list_files():
    if path_filter not in f:
        continue
    result = move(f)
    if not result:
        continue
    count, moved, kept = result
    common.format_file(f)
    touched += 1
    print("%-52s %2d declarations, %2d moved, left: %s"
          % (f.rsplit("/", 1)[-1][:-4], count, moved, " ".join(kept) or "-"))
print("%d file(s) changed" % touched)

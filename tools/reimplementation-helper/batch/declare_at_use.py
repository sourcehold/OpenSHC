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
  declare_at_use.py [path-filter] [--apply]
"""

import re
import sys

import common

args = [a for a in sys.argv[1:] if a != "--apply"]
apply_changes = "--apply" in sys.argv[1:]
path_filter = args[0] if args else ""

DECL = re.compile(r"^(?P<type>(?:unsigned\s+|const\s+)*[A-Za-z_][\w:]*)\s+"
                  r"(?P<ptr>\**)\s*(?P<name>[A-Za-z_]\w*)\s*"
                  r"(?P<arr>\[[^\]]*\])?\s*;$")


def is_case_label(line):
    """True for a `case ...:` or `default:` label.

    Deliberately not a regex: an earlier version of this check compiled a literal
    backspace where a word boundary was meant, so it matched nothing and the guard
    below passed every switch it was written to reject.
    """
    s = line.strip()
    return s.startswith("case ") or s.startswith("default:") or s.startswith("default :")


def depths(lines):
    """Lowest brace depth each line's own code sits at.

    A line is recorded at the minimum depth it reaches rather than the depth it opens at,
    so a use on a closing-brace line is seen at the *outer* depth. `} while (cond);` is
    the case that matters: recorded at the inner depth it slipped past the scope check
    below, and a declaration moved into the do-block left the while condition referring
    to an out-of-scope variable, which does not compile.
    """
    out, d = [], 0
    for line in lines:
        code = re.sub(r"//.*", "", line)
        low = d
        for ch in code:
            if ch == "{":
                d += 1
            elif ch == "}":
                d -= 1
                low = min(low, d)
        out.append(low)
    return out


def depths_after(lines):
    """Brace depth *after* each line, which is what says where a block ends.

    depths() reports the lowest depth a line reaches so that a use on a closing line is
    seen outside the block. That is the wrong measure for block extent: it makes an inner
    `}` look like the end of the enclosing block, which stopped the case-label scan below
    before it reached the label it was looking for.
    """
    out, d = [], 0
    for line in lines:
        code = re.sub(r"//.*", "", line)
        d += code.count("{") - code.count("}")
        out.append(d)
    return out


def move(path, write=True):
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
        # A `case` label reached after the declaration jumps over its initialisation,
        # which MSVC rejects with C2360. Brace depth cannot see this on its own, since
        # every arm of a switch shares one depth. The scan also has to run to the end of
        # the block enclosing the first use rather than to the last use, because the
        # variable stays in scope that far: in calculateHoveredTile the offending label
        # sits three lines *after* the last use of imageX.
        after = depths_after(lines)
        end = first + 1
        while end < len(lines) and after[end] >= d[first]:
            end += 1
        if any(d[n] == d[first] and is_case_label(lines[n])
               for n in range(first + 1, end)):
            continue
        lines[first] = re.sub(r"^(\s*)%s\s*=" % re.escape(var),
                              lambda m: "%s%s %s%s =" % (m.group(1), vtype, ptr, var),
                              lines[first], count=1)
        drop.add(decl_at)

    if not drop:
        return None
    kept = [d[0] for d in decls if d[4] not in drop]
    if write:
        common.write_text(path, head + "\n".join(l for n, l in enumerate(lines) if n not in drop))
    return len(decls), len(drop), kept


def main():
    touched = 0
    for f in common.list_files():
        if path_filter not in f:
            continue
        result = move(f, write=apply_changes)
        if not result:
            continue
        count, moved, kept = result
        if apply_changes:
            common.format_file(f)
        touched += 1
        print("%-52s %2d declarations, %2d moved, left: %s"
              % (f.rsplit("/", 1)[-1][:-4], count, moved, " ".join(kept) or "-"))
    print("%d file(s) changed%s"
          % (touched, "" if apply_changes else " (dry run, pass --apply)"))


if __name__ == "__main__":
    main()

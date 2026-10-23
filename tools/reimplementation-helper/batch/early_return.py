"""Turn a function whose whole body is one big `if (guard) { ... }` into early-return form.

Ghidra keeps the bounds check of every PathFindingState search as a guard wrapping
the entire function body:

    if (x <= 399 && y <= 399 && map[..] != '\0') {
        <200 lines>
    }
    return FALSE;

The original source almost certainly rejected the bad case first, which also stops
MSVC inlining the cold return block in the middle of the hot path (the RET flag of
diff_triage.py). This rewrites it to

    if (399 < x || 399 < y || map[..] == '\0') {
        return FALSE;
    }
    <200 lines, dedented>
    return FALSE;

usage: early_return.py [filter] [--apply]   (dry run unless --apply)
"""

import re
import sys

import common

FUNCTION_LINE = re.compile(r"^[ \t]*// FUNCTION: STRONGHOLDCRUSADER 0x[0-9A-Fa-f]+[ \t]*$", re.M)
FLIP = {"<": ">=", "<=": ">", ">": "<=", ">=": "<", "==": "!=", "!=": "=="}
SPLIT = re.compile(r"\s+&&\s+")
TERM = re.compile(r"^\(?\s*(?P<l>.+?)\s*(?P<op><=|>=|==|!=|<|>)\s*(?P<r>.+?)\s*\)?$", re.S)


def balanced(text):
    return text.count("(") == text.count(")") and text.count("[") == text.count("]")


def invert(cond):
    """De Morgan over a top-level `&&` chain of simple comparisons, or None."""
    parts, depth, start = [], 0, 0
    for i, c in enumerate(cond):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif depth == 0 and cond.startswith("&&", i) and (i == start or cond[i - 1].isspace()):
            parts.append(cond[start:i])
            start = i + 2
        elif depth == 0 and cond.startswith("||", i):
            return None  # mixed chain: the inversion would need brackets we cannot place safely
    parts.append(cond[start:])
    out = []
    for part in parts:
        part = " ".join(part.split()).strip()
        while part.startswith("(") and part.endswith(")") and balanced(part[1:-1]):
            part = part[1:-1].strip()
        m = TERM.match(part)
        if not m or not balanced(m.group("l")) or not balanced(m.group("r")):
            return None
        if "&&" in part or "||" in part:
            return None
        out.append("%s %s %s" % (m.group("l"), FLIP[m.group("op")], m.group("r")))
    return " || ".join(out)


def rewrite(text):
    m = FUNCTION_LINE.search(text)
    if not m:
        return text, 0
    open_brace = text.find("{", text.index("\n", m.end()))
    if open_brace < 0:
        return text, 0
    depth, i = 0, open_brace
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                break
        i += 1
    body = text[open_brace + 1:i]
    # the body must be exactly: one if (...) { ... } then one return statement
    g = re.match(r"\n(?P<pre>.*?)(?P<ind>[ \t]+)if \((?P<cond>[^\n]*?)\) \{\n(?P<inner>.*)\n(?P=ind)\}\n(?P=ind)(?P<ret>return[^;]*;)\n[ \t]*$",
                 body, re.S)
    if not g:
        return text, 0
    cond = " ".join(g.group("cond").split())
    # only the whole-function bounds guard, not some small trailing `if`
    if "<= 399" not in cond and "DAT_BinaryTileMap400x400" not in cond:
        return text, 0
    if g.group("inner").count("\n") < 10:
        return text, 0
    inverted = invert(cond)
    if inverted is None:
        return text, 0
    indent = g.group("ind")
    inner = "\n".join(line[4:] if line.startswith(indent + "    ") else line
                      for line in g.group("inner").split("\n"))
    new = "\n%s%sif (%s) {\n%s    %s\n%s}\n%s\n%s%s\n" % (
        g.group("pre"), indent, inverted, indent, g.group("ret"), indent, inner, indent, g.group("ret"))
    return text[:open_brace + 1] + new + text[i:], 1


def main():
    apply = "--apply" in sys.argv
    args = [a for a in sys.argv[1:] if a != "--apply"]
    filter_ = args[0] if args else ""
    total = 0
    for path in common.list_files():
        if filter_ and filter_ not in path.replace("\\", "/"):
            continue
        text = common.read_text(path)
        new, n = rewrite(text)
        if n:
            total += n
            print(path.split("/")[-1][:-4])
            if apply:
                common.write_text(path, new)
    print("%d function(s) turned into early-return form%s" % (total, "" if apply else " (dry run, pass --apply)"))


main()

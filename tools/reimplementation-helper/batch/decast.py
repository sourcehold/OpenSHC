"""Collapse the decompiler's doubled casts, e.g. (int)((int)(x)) -> (int)(x).

Only a cast applied to a *whole* casted operand is removed. `(int)((int)X + Y)` looks the
same textually but is not a doubled cast: there the inner cast covers X alone, and
dropping it moves the conversion onto the sum, which changes the generated code. The
`sole_operand` check rejects those.

Measured as code-generation neutral over the UnitsState namespace (19 casts, no change in
any function), so it is a readability pass -- but re-measure after running it.

usage:
  decast.py [path-filter]
"""

import sys

import common

path_filter = sys.argv[1] if len(sys.argv) > 1 else ""

# (outer, inner) pairs where dropping the inner cast cannot change the conversion
PAIRS = [("int", "int"), ("uint", "uint"), ("short", "short"), ("ushort", "ushort"),
         ("uint", "int"), ("int", "uint"), ("short", "int"), ("ushort", "int")]


def match_paren(s, i):
    depth = 0
    while i < len(s):
        if s[i] == "(":
            depth += 1
        elif s[i] == ")":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    raise ValueError("unbalanced")


def is_group(s):
    s = s.strip()
    return s.startswith("(") and match_paren(s, 0) == len(s) - 1


def sole_operand(s):
    """True if s is one operand rather than part of a wider expression."""
    s = s.strip()
    if is_group(s):
        return True
    depth = 0
    for ch in s:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif depth == 0 and ch in "+-*/%&|^<>=!?,":
            return False
    return True


def collapse_once(text):
    for outer, inner in PAIRS:
        needle = "(%s)((%s)" % (outer, inner)
        i = text.find(needle)
        while i != -1:
            try:
                close = match_paren(text, i + len(outer) + 2)
            except ValueError:
                i = text.find(needle, i + 1)
                continue
            rest = text[i + len(outer) + 3:close][len(inner) + 2:].strip()
            if rest and sole_operand(rest):
                body = rest if is_group(rest) else "(%s)" % rest
                return text[:i] + "(%s)%s" % (outer, body) + text[close + 1:], True
            i = text.find(needle, i + 1)
    return text, False


total = 0
for f in common.list_files():
    if path_filter not in f:
        continue
    text = common.read_text(f).replace("\r\n", "\n")
    n = 0
    while True:
        text, changed = collapse_once(text)
        if not changed:
            break
        n += 1
        if n > 200:
            sys.exit("%s: not converging" % f)
    if n:
        common.write_text(f, text)
        common.format_file(f)
        print("%-52s %d" % (f.rsplit("/", 1)[-1][:-4], n))
        total += n
print("%d doubled cast(s) collapsed" % total)

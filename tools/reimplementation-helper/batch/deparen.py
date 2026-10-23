"""Drop the decompiler's redundant parentheses from if/while conditions.

The decompiler brackets every operand, so conditions arrive looking like

    if ((((a == 1) && (b == 2)) && (c == 3)))

A group is unwrapped only when C's precedence makes it provably superfluous: its own
loosest top-level operator must be the same as the one joining it to its siblings (so an
&& chain flattens), or it must be a bare comparison. Everything else keeps its brackets:

  - a group holding an assignment or a comma operator (the decompiler emits those inside
    conditions, and they are load-bearing),
  - `(a || b) && c`, where dropping them changes the meaning,
  - `(x & 7) == 0`, where & binds looser than ==,
  - `(a && b) || c`, which is legal to unwrap but clearer kept.

Run test_deparen.py after changing the precedence table; an earlier version of this script
silently turned `(a != 0 || b != 0) && (x & 0x100) == 0` into a different expression that
still compiled.

Code-generation neutral in the cases measured so far, but re-measure after running it.

usage:
  deparen.py [path-filter] [--apply]
"""

import argparse
import re

import common

# loosest first; a lower rank binds less tightly
LEVELS = [[","], ["="], ["||"], ["&&"], ["|"], ["^"], ["&"], ["==", "!="],
          ["<=", ">=", "<", ">"]]
COMPARISON = 7          # index in LEVELS of ==/!=; anything at or past this is a comparison


def match_paren(s, i):
    depth = 0
    while i < len(s):
        if s[i] in "([":
            depth += 1
        elif s[i] in ")]":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def scan_top(s):
    """Yield (index, level, token) for every top-level operator."""
    i = 0
    while i < len(s):
        if s[i] in "([":
            j = match_paren(s, i)
            i = (j + 1) if j != -1 else i + 1
            continue
        for level, tokens in enumerate(LEVELS):
            hit = None
            for tok in tokens:
                if not s.startswith(tok, i):
                    continue
                if tok == "=" and (s[i - 1:i] in "=!<>" or s[i + 1:i + 2] == "="):
                    continue
                if tok in ("<", ">") and s[i - 1:i + 1] == "->":
                    continue
                hit = tok
                break
            if hit:
                yield i, level, hit
                i += len(hit) - 1
                break
        i += 1


def rank(s):
    """Level of the loosest top-level operator, or len(LEVELS) when there is none."""
    best = len(LEVELS)
    for _, level, _ in scan_top(s):
        best = min(best, level)
    return best


def split_top(s, tok):
    parts, last = [], 0
    for idx, _, t in scan_top(s):
        if t == tok and idx >= last:
            parts.append(s[last:idx])
            last = idx + len(tok)
    parts.append(s[last:])
    return parts


def is_group(s):
    s = s.strip()
    return s.startswith("(") and match_paren(s, 0) == len(s) - 1


def simplify(expr):
    """Simplify inside expr. Its own outer brackets are the caller's to judge, since only
    the caller knows which operator binds it to its siblings."""
    expr = expr.strip()
    r = rank(expr)
    if r >= len(LEVELS):
        return expr
    tokens = [t for _, level, t in scan_top(expr) if level == r]
    if not tokens or any(t != tokens[0] for t in tokens):
        return expr                               # mixed operators at one level: leave it
    tok = tokens[0]
    out = []
    for part in split_top(expr, tok):
        part = part.strip()
        while is_group(part):
            inner = part[1:-1].strip()
            ri = rank(inner)
            if ri <= 1 or not (ri == r or ri >= COMPARISON):
                break
            part = inner
        out.append(simplify(part))
    return (" %s " % tok).join(out)


CONDITION = re.compile(r"(?m)^(\s*)(\}\s*else\s+)?(if|while)\s*\(")


def process(text):
    out, pos, n = [], 0, 0
    for m in CONDITION.finditer(text):
        if m.start() < pos:
            continue
        open_at = text.index("(", m.end() - 1)
        close_at = match_paren(text, open_at)
        if close_at == -1:
            continue
        flat = " ".join(text[open_at + 1:close_at].split())
        # the if's own brackets already group the whole condition, so one redundant layer
        # directly inside them can always go
        outer = flat
        while is_group(outer) and rank(outer[1:-1]) > 1:
            outer = outer[1:-1].strip()
        new = simplify(outer)
        if new != flat and ("((" in flat or "))" in flat):
            out.append(text[pos:open_at + 1])
            out.append(new)
            pos = close_at
            n += 1
    out.append(text[pos:])
    return "".join(out), n


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("path_filter", nargs="?", default="")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()

    total = 0
    for f in common.list_files():
        if args.path_filter not in f:
            continue
        new, n = process(common.read_text(f).replace("\r\n", "\n"))
        if not n:
            continue
        print("%-52s %d" % (f.rsplit("/", 1)[-1][:-4], n))
        total += n
        if args.apply:
            common.write_text(f, new)
            common.format_file(f)
    print("%d condition(s) simplified%s" % (total, "" if args.apply else " (dry run, pass --apply)"))

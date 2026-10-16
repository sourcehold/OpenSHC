"""Rewrite the compiler's signed power-of-two division back into a division.

For a signed int the compiler cannot just shift, because shifting rounds towards
negative infinity while C division truncates towards zero. So it biases the value first
and the decompiler faithfully reports the bias:

    (x + (x >> 0x1f & 7U)) >> 3          ->   x / 8
    (int)(x + (x >> 0x1f & 0xfU)) >> 4   ->   x / 16

The identity holds for every mask of the form 2^k - 1 paired with a shift of k, and MSVC
regenerates exactly the same instructions from the division, so this is normally match
neutral -- but measure it anyway, since nothing here is predictable.

Only the signed form is rewritten. `(x >> 3)` on its own is an unsigned division or a
genuine shift and is left alone.

usage:
  undiv.py [path-filter] [--apply]
"""

import argparse
import re

import common

SHIFT = re.compile(r"\A\s*>>\s*(\d+)")
# the inside of a bias term, once its own brackets are known: "x >> 0x1f & 7U"
BIAS = re.compile(r"\A\s*(.+)\s*>>\s*0x1f\s*&\s*(0x[0-9a-fA-F]+|\d+)U?\s*\Z", re.S)


def open_paren(text, close):
    """Index of the '(' matching the ')' at `close`."""
    depth = 0
    for i in range(close, -1, -1):
        if text[i] == ")":
            depth += 1
        elif text[i] == "(":
            depth -= 1
            if depth == 0:
                return i
    return -1


def close_paren(text, opening):
    depth = 0
    for i in range(opening, len(text)):
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            depth -= 1
            if depth == 0:
                return i
    return -1


def normalize(expr):
    """Strip a redundant (int) cast and one layer of brackets off the dividend."""
    expr = expr.strip()
    if expr.startswith("(int)"):
        expr = expr[5:].strip()
    while expr.startswith("(") and close_paren(expr, 0) == len(expr) - 1:
        expr = expr[1:-1].strip()
    return expr


def enclosing_group(text, i):
    """(open, close) of the innermost bracket pair containing index i, or None."""
    depth, opening = 0, -1
    for j in range(i, -1, -1):
        if text[j] == ")":
            depth += 1
        elif text[j] == "(":
            if depth == 0:
                opening = j
                break
            depth -= 1
    if opening == -1:
        return None
    closing = close_paren(text, opening)
    return None if closing < i else (opening, closing)


def rewrite_one(text, at):
    """Rewrite the division whose ">> 0x1f" sits at index `at`, or return None."""
    group = enclosing_group(text, at)
    if not group:
        return None
    m = BIAS.match(text[group[0] + 1:group[1]])
    if not m:
        return None
    mask = int(m.group(2), 0)
    shift = mask.bit_length()
    if mask + 1 != 1 << shift:            # not 2^k - 1: not this idiom
        return None
    dividend = normalize(m.group(1))

    # the brackets one level further out must hold "dividend + bias"
    outer = enclosing_group(text, group[0] - 1)
    if not outer:
        return None
    sum_open, sum_close = outer
    lhs, plus, rhs = text[sum_open + 1:sum_close].partition("+")
    if not plus or normalize(lhs) != dividend:
        return None
    if rhs.strip() != text[group[0]:group[1] + 1].strip():
        return None

    start, end = sum_open, sum_close + 1
    m = SHIFT.match(text[end:])
    if not m or int(m.group(1)) != shift:
        return None
    # A signed cast around the sum only existed to make the shift arithmetic, and the bias
    # itself proves the dividend is already signed, so the cast goes with the shift.
    if text[:sum_open].rstrip().endswith("(int)"):
        start = text.rindex("(int)", 0, sum_open)
    return text[:start] + "%s / %d" % (dividend, 1 << shift) + text[end + m.end():]


def process(text):
    n = 0
    while True:
        for at in [m.start() for m in re.finditer(r">>\s*0x1f", text)]:
            new = rewrite_one(text, at)
            if new is not None:
                text, n = new, n + 1
                break
        else:
            return text, n


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
    print("%d division(s) restored%s"
          % (total, "" if args.apply else " (dry run, pass --apply)"))

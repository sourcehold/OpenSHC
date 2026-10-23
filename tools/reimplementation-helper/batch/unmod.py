"""Rewrite the compiler's signed power-of-two remainder back into a modulo.

`x % 16` on a signed int cannot just mask, because the result has to keep x's sign. The
compiler masks the low bits together with the sign bit and then repairs the negative case,
and the decompiler reports both halves as separate statements:

    v = x & 0x8000000f;
    if ((int)v < 0) {
        v = (v - 1 | 0xfffffff0) + 1;
    }

That is `v = x % 16`. The mask's low bits and the `|` constant have to agree with each
other (`0x…0f` with `0xfffffff0`), which is what makes the pattern safe to recognise: a
plain `x & 0xf` with no repair is a mask on a value already known non-negative and is left
alone.

Companion to undiv.py, which does the same job for division. Measure afterwards.

usage:
  unmod.py [path-filter] [--apply]
"""

import argparse
import re

import common

# "v = EXPR & 0x8000000f;" then the negative-case repair, as clang-format leaves them
# clang-format wraps these across lines freely, so every gap has to allow newlines
IDIOM = re.compile(
    r"(?P<indent>[ ]*)(?P<decl>(?:[A-Za-z_][\w:]*[ ]+)?)(?P<var>[\w:.\[\]>-]+)\s*=\s*"
    # the dividend cannot cross a statement or block boundary; bounding it this way also
    # keeps the engine from backtracking across the whole file
    r"(?P<expr>[^;{}]+?)\s*&\s*0x8000000(?P<mask>[0-9a-fA-F])\s*;\s*\n"
    r"\s*if\s*\(\s*\(int\)(?P<var2>[\w:.\[\]>-]+)\s*<\s*0\s*\)\s*\{\s*\n"
    r"\s*(?P<var3>[\w:.\[\]>-]+)\s*=\s*\(\s*(?P<var4>[\w:.\[\]>-]+)\s*-\s*1\s*\|\s*"
    r"0x(?P<comp>[0-9a-fA-F]{8})\s*\)\s*\+\s*1\s*;\s*\n"
    r"\s*\}[ ]*\n",
    re.S)


def replace(m):
    mask = int(m.group("mask"), 16)
    modulus = mask + 1
    if modulus & mask:                                  # mask is not 2^k - 1
        return m.group(0)
    if int(m.group("comp"), 16) != (~mask & 0xffffffff):  # repair disagrees with the mask
        return m.group(0)
    var = m.group("var")
    if not all(g == var for g in m.group("var2", "var3", "var4")):
        return m.group(0)
    expr = m.group("expr").strip()
    # The repair only exists because the operand is signed -- an unsigned remainder is a
    # bare `and`. So the dividend has to be signed here too, or `%` compiles to that bare
    # `and` and stops matching. Drop the decompiler's U suffixes and cast if need be.
    expr = re.sub(r"\b(\d+)U\b", r"\1", expr)
    # the modulo binds tighter than whatever built the dividend, so bracket a dividend that
    # is built with a looser operator. Member arrows and bracketed groups are not operators
    # for this purpose, so drop them before looking.
    bare = re.sub(r"\([^()]*\)", "", expr).replace("->", "")
    if re.search(r"[-+*/|^]|>>|<<", bare):
        expr = "(%s)" % expr
    elif not expr.startswith("(int)"):
        expr = "(int)%s" % expr
    return "%s%s%s = %s %% %d;\n" % (m.group("indent"), m.group("decl"), var, expr, modulus)


def process(text):
    new, n = IDIOM.subn(replace, text)
    # subn counts every match, including the ones replace() handed back unchanged
    return new, sum(1 for _ in IDIOM.finditer(text)) - sum(1 for _ in IDIOM.finditer(new))


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
    print("%d modulo(s) restored%s" % (total, "" if args.apply else " (dry run, pass --apply)"))

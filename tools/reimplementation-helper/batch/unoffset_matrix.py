"""Resolve the decompiler's byte arithmetic on clockwiseCardinalTranslationMatrix.

Where the direction index is not a plain loop counter, Ghidra gives up on the array
and indexes the matrix by hand:

    *(short*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar3 * 8 + 0xc)

Each entry is 8 bytes with xOffset at +0 and yOffset at +4, so that byte offset names
entry `iVar3 + 1`'s yOffset:

    DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar3 + 1].short_.yOffset

usage: unoffset_matrix.py [filter] [--apply]   (dry run unless --apply)
"""

import re
import sys

import common

MATRIX = "DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix"
ENTRY = 8

# *(short*)((int)MATRIX + <idx> * 8 + <off>)   -- the whitespace is whatever clang-format left
PATTERN = re.compile(
    r"\*\((?P<type>short|int)\*\)\(\s*\(int\)" + re.escape(MATRIX)
    + r"\s*\+\s*(?P<idx>[A-Za-z_]\w*)\s*\*\s*8(?:\s*\+\s*(?P<off>0x[0-9a-fA-F]+|\d+))?\s*\)")


def convert(text):
    def repl(m):
        off = int(m.group("off"), 0) if m.group("off") else 0
        entry, within = divmod(off, ENTRY)
        if within not in (0, 4):
            return m.group(0)
        index = m.group("idx") if entry == 0 else "%s + %d" % (m.group("idx"), entry)
        return "%s[%s].%s.%s" % (MATRIX, index, m.group("type") + "_",
                                 "xOffset" if within == 0 else "yOffset")

    return PATTERN.subn(repl, text)


def main():
    apply = "--apply" in sys.argv
    args = [a for a in sys.argv[1:] if a != "--apply"]
    filter_ = args[0] if args else ""
    total = 0
    for path in common.list_files():
        if filter_ and filter_ not in path.replace("\\", "/"):
            continue
        text = common.read_text(path)
        new, n = convert(text)
        if n:
            total += n
            print("%-52s %d" % (path.split("/")[-1][:-4], n))
            if apply:
                common.write_text(path, new)
    print("%d matrix offset(s) resolved to fields%s" % (total, "" if apply else " (dry run, pass --apply)"))


main()

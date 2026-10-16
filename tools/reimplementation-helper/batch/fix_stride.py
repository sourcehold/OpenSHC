"""Repair struct-pointer walks that kept the decompiler's element stride.

Ghidra walks these loops with a `short*` or `int*`, so it steps the pointer by
`sizeof(struct) / 2` or `/ 4`. When the import gave the variable the struct type back, the
step has to become 1 - `ptrUnit = ptrUnit + 0x248` on a `Unit*` (0x490 bytes) advances
0x248 structs, which is 0xa6880 bytes instead of 0x490.

A silent wrong-memory bug, and the asm shows it directly (`add esi, 0xa6880` against the
original's `add esi, 0x490`).

usage: fix_stride.py [filter] [--apply]
"""

import re
import sys

import common

SIZES = {}


def struct_size(type_name):
    """sizeof(T) from the static_assert in the header that defines T."""
    if type_name not in SIZES:
        SIZES[type_name] = None
        for path in common.ROOT.joinpath("src/OpenSHC").rglob("%s.hpp" % type_name):
            m = re.search(r"static_assert_cpp98_obj\(sizeof\(%s\) == (\d+)" % type_name, path.read_text(encoding="utf-8"))
            if m:
                SIZES[type_name] = int(m.group(1))
                break
    return SIZES[type_name]


apply = "--apply" in sys.argv
rest = [a for a in sys.argv[1:] if a != "--apply"]
filter_ = rest[0] if rest else ""
WALK = re.compile(r"^(\s*)(\w+) = \2 \+ (0x[0-9a-f]+|\d+);$", re.M)

fixed = 0
for f in common.list_files():
    if filter_ not in f:
        continue
    text = common.read_text(f)
    out, hits = text, []
    for m in WALK.finditer(text):
        name, step = m.group(2), int(m.group(3), 0)
        decl = re.search(r"\b([A-Z]\w+)\*\s*%s\b" % re.escape(name), text)
        if not decl or step == 1:
            continue
        size = struct_size(decl.group(1))
        if size is None or step * size == size:
            continue
        # the stride is the struct size counted in 1-, 2- or 4-byte elements
        if step not in (size, size // 2, size // 4) or size % step:
            continue
        hits.append((m.group(0), "%s%s = %s + 1;" % (m.group(1), name, name), decl.group(1), step))
    for old, new, type_name, step in hits:
        out = out.replace(old, new)
        print("%-55s %s* += 0x%x -> 1" % (f.split("/")[-1], type_name, step))
    if hits:
        fixed += len(hits)
        if apply:
            common.write_text(f, out)
print("%d struct-pointer stride(s)%s" % (fixed, "" if apply else " (dry run, pass --apply)"))

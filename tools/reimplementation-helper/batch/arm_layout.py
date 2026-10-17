"""Print the original's and our switch-arm layout order, from reccmp's jump tables.

A jump table's entries are in case order (MSVC assigns indices by ascending case value and
gives `default` the last one), so sorting the entries by offset gives the order the arms are
laid out in - which for MSVC is the source order, modulo arms it chooses to move.

usage: arm_layout.py FUNCTION TABLE_INDEX case,case,...   (cases ascending, no default)
"""
import re
import subprocess
import sys

func, which, cases = sys.argv[1], int(sys.argv[2]), [int(c, 0) for c in sys.argv[3].split(",")]
out = subprocess.run(["python", "tools/reimplementation-helper/batch/reccmp_report.py", "diff", func],
                     capture_output=True, text=True).stdout.split("\n")
tables, cur, seen = [], None, 0
for l in out:
    if l.strip().endswith("Jump table:"):
        seen += 1
        cur = {"-": [], "+": []}
        tables.append(cur)
        continue
    if cur is None:
        continue
    m = re.match(r"^([-+ ])start \+ (0x[0-9a-f]+)", l)
    if not m:
        if l.strip() and "start +" not in l:
            cur = None
        continue
    sign, off = m.group(1), int(m.group(2), 16)
    if sign == " ":
        cur["-"].append(off); cur["+"].append(off)
    else:
        cur[sign].append(off)

t = tables[which]
names = ["%x" % c for c in cases] + ["default"]
for side, label in (("-", "orig"), ("+", "ours")):
    offs = t[side]
    if len(offs) != len(names):
        print("%s: %d entries, expected %d - alignment unreliable" % (label, len(offs), len(names)))
        continue
    order = sorted(range(len(offs)), key=lambda i: offs[i])
    print("%s: %s" % (label, ", ".join(names[i] for i in order)))

"""Per-arm byte sizes of a jump-table switch, original vs ours, from reccmp's tables.

The jump-table entries are in case order, so sorting them by offset gives both the arm layout
and - by differencing consecutive offsets - each arm's size. That turns "this 800-instruction
function is 55%" into a short list of arms that are actually the wrong length.

usage: arm_sizes.py FUNCTION TABLE_INDEX case,case,...   (cases ascending, no default)
"""
import re
import subprocess
import sys

func, which = sys.argv[1], int(sys.argv[2])
cases = [int(c, 0) for c in sys.argv[3].split(",")]
names = ["%x" % c for c in cases] + ["default"]

out = subprocess.run(["python", "tools/reimplementation-helper/batch/reccmp_report.py", "diff", func],
                     capture_output=True, text=True).stdout.split("\n")
tables, cur = [], None
for l in out:
    if l.strip().endswith("Jump table:"):
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
for side in ("-", "+"):
    if len(t[side]) != len(names):
        sys.exit("%s side has %d entries, expected %d" % (side, len(t[side]), len(names)))


def layout_and_sizes(offs):
    order = sorted(range(len(offs)), key=lambda i: offs[i])
    sz = {}
    for k in range(len(order) - 1):
        sz[names[order[k]]] = offs[order[k + 1]] - offs[order[k]]
    sz[names[order[-1]]] = None
    return [names[i] for i in order], sz


lo, so = layout_and_sizes(t["-"])
lu, su = layout_and_sizes(t["+"])
print("layout identical: %s" % (lo == lu))
if lo != lu:
    print("  orig: %s" % ", ".join(lo))
    print("  ours: %s" % ", ".join(lu))
print("%-9s %6s %6s  delta" % ("arm", "orig", "ours"))
total = 0
for n in lo:
    a, b = so[n], su.get(n)
    if a is None or b is None:
        print("%-9s %6s %6s  (last arm, size unknown)" % (n, a, b))
        continue
    total += b - a
    print("%-9s %6d %6d  %+5d%s" % (n, a, b, b - a, "   <<<" if abs(b - a) >= 6 else ""))
print("total %+d bytes over %d arms" % (total, len(lo) - 1))

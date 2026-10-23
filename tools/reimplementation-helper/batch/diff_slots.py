"""Census of the `[esp + N]` slots each side touches, to find a local too many.

usage: diff_slots.py NAME-SUBSTRING

Prints every stack slot with how often it is accessed, on the original and on
our side.  Use it after diff_triage.py reports a FRAME mismatch: one extra
distinct slot on our side is one local the original does not have, and the slot
with the lowest access count is usually the culprit.  Grep the diff for that
slot to see what writes it - a 16-bit `mov word ptr [esp+N]` means a `short`
local the original keeps in a register or widens to `int`.
"""

import re
import sys

import common

if len(sys.argv) < 2:
    sys.exit(__doc__)
want = sys.argv[1]
SLOT = re.compile(r"\[esp \+ (0x[0-9a-f]+)\]")

for f, e, address in common.entries(common.load_diff()):
    if e is None or want not in e["name"] or not e.get("diff"):
        continue
    orig, ours = common._asm_lines(e)
    counts = []
    for stream in (orig, ours):
        c = {}
        for line in stream:
            for m in SLOT.finditer(line):
                v = int(m.group(1), 16)
                c[v] = c.get(v, 0) + 1
        counts.append(c)
    o, u = counts
    print("### %s %.1f%%" % (e["name"], float(e["matching"]) * 100))
    print("  orig %2d slots: %s" % (len(o), " ".join("%#x:%d" % kv for kv in sorted(o.items()))))
    print("  ours %2d slots: %s" % (len(u), " ".join("%#x:%d" % kv for kv in sorted(u.items()))))
    only_ours = sorted(set(u) - set(o))
    if only_ours:
        print("  only ours: %s" % " ".join("%#x (%d uses)" % (k, u[k]) for k in only_ours))

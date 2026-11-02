"""Comparisons written with their operands the wrong way round.

`if (a < b)` and `if (b > a)` are the same test and MSVC emits a different `cmp` for
each: the left operand goes first. So a comparison written the other way round costs
the `cmp` and its `jcc` or `setcc`, and neither diff_jcc nor diff_inv_jcc reports it -
the branch sense is consistent with the operands, so nothing looks inverted.

It found +10.1 on snapshotSelectionTribeAndComputeStance (`cmp ecx, esi; setge al`
against our `cmp esi, ecx; setle al`) and a two-instruction miss in
addUnitsToTribeAndComputeMovementSpeed.

This looks for an orig `cmp A, B` facing an ours `cmp B, A` in the same diff block,
with the following jcc or setcc mirrored to match - which is what makes it a swap
rather than an unrelated pair.

usage: diff_cmp_operands.py
"""

import re
import sys

import common

MIRROR = {"jl": "jg", "jg": "jl", "jle": "jge", "jge": "jle",
          "jb": "ja", "ja": "jb", "jbe": "jae", "jae": "jbe",
          "setl": "setg", "setg": "setl", "setle": "setge", "setge": "setle",
          "setb": "seta", "seta": "setb", "setbe": "setae", "setae": "setbe"}

CMP = re.compile(r"^cmp\s+([^,]+),\s*(.+)$")


def operands(line):
    m = CMP.match(common._normalize(line).strip())
    return (m.group(1).strip(), m.group(2).strip()) if m else None


def follower(rows, i):
    for r in rows[i + 1:i + 3]:
        w = r.strip().split()
        if w and w[0] in MIRROR:
            return w[0]
    return None


def main():
    hits = 0
    for f, e, a in common.entries(common.load_diff()):
        if not e or float(e["matching"]) >= 1.0:
            continue
        found = []
        for hunk in e.get("diff") or []:
            for block in hunk[1]:
                o = [r[1] for r in block.get("orig", [])]
                r_ = [r[1] for r in block.get("recomp", [])]
                for i, ol in enumerate(o):
                    oo = operands(ol)
                    if not oo:
                        continue
                    for j, rl in enumerate(r_):
                        ro = operands(rl)
                        if not ro or ro != (oo[1], oo[0]):
                            continue
                        of, rf = follower(o, i), follower(r_, j)
                        if of and rf and MIRROR.get(of) == rf:
                            found.append((ol.strip(), of, rl.strip(), rf))
                            break
        if found:
            hits += 1
            print("### %s %.1f%%" % (e["name"].split("::")[-1],
                                     float(e["matching"]) * 100))
            for ol, of, rl, rf in found[:4]:
                print("    orig  %-46s %s" % (ol[:46], of))
                print("    ours  %-46s %s" % (rl[:46], rf))
    print("\n%d function(s) with a swapped comparison" % hits)


main()

"""Inverted conditional jumps, including where the diff has slipped out of alignment.

An `if`/`else` whose arms are the wrong way round costs far more than the one branch
it flips: the arm the original falls through into gets emitted in the far block
instead, and every branch past it shifts. Two of these were worth +7.7
(updateTribeCombatStanceBehavior) and +0.7 (sortTribePathDestinationsByCost, which
had two in its first ten lines).

diff_jcc.py only compares jcc pairs the differ managed to line up, and an inversion
tends to misalign the very block it sits in - so neither of those showed up there.
This walks each diff block and reports an orig-only jcc facing a recomp-only jcc of
the opposite sense.

Not every hit is real: any orig jcc in a block is paired against any opposite recomp
jcc in the same block, so expect false positives in blocks holding several branches.
Read the diff around each hit before changing anything. A good sign is the original
jumping a short distance where ours jumps a long one, or vice versa.

usage: diff_inv_jcc.py        (reads the last reccmp run; re-run reccmp first)
"""
import sys, os, re
sys.path.insert(0, os.path.join("tools", "reimplementation-helper", "batch"))
import common

INV = {}
for a, b in [("je","jne"),("jz","jnz"),("jl","jge"),("jle","jg"),("jb","jae"),
             ("jbe","ja"),("js","jns"),("jo","jno"),("jp","jnp")]:
    INV[a] = b; INV[b] = a

def mnem(row):
    return row.split()[0].lower() if row.strip() else ""

hits = 0
for f, e, addr in common.entries(common.load_diff()):
    if not e or float(e["matching"]) >= 1.0:
        continue
    found = []
    for hunk in e.get("diff") or []:
        for block in hunk[1]:
            o = [r[1] for r in block.get("orig", [])]
            r_ = [r[1] for r in block.get("recomp", [])]
            if not o or not r_:
                continue
            oj = [x for x in o if mnem(x) in INV]
            rj = [x for x in r_ if mnem(x) in INV]
            for x in oj:
                for y in rj:
                    if INV[mnem(x)] == mnem(y):
                        found.append((mnem(x), mnem(y), o[0][:58], r_[0][:58]))
                        break
                else:
                    continue
                break
    if found:
        hits += 1
        print("### %s %.1f%%  (%d)" % (e["name"].split("::")[-1], float(e["matching"])*100, len(found)))
        for om, rm, oc, rc in found[:3]:
            print("    orig %-4s / ours %-4s   orig-block: %s" % (om, rm, oc))
            print("    %34s ours-block: %s" % ("", rc))
print("\n%d function(s) with an inverted branch" % hits)

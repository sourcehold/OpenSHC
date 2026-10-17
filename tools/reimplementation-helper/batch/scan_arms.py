"""Report je/jne (and jz/jnz) pairs where the original branches the other way.

A flipped equality branch after the same compare means the two arms of an if/else are
the other way round in the original: the arm it falls into is the one it keeps inline.
"""
import re
import sys

import common

FLIP = {"je": "jne", "jne": "je"}
for f, e, _ in common.entries(common.load_diff()):
    if e is None or float(e["matching"]) >= 1:
        continue
    hits = []
    for hunk in e.get("diff") or []:
        for block in hunk[1]:
            orig = [r[1] for r in block.get("orig", [])]
            recomp = [r[1] for r in block.get("recomp", [])]
            for a in orig:
                oa = a.split("\t")[0].strip().split()
                if not oa or oa[0] not in FLIP:
                    continue
                for b in recomp:
                    ob = b.split("\t")[0].strip().split()
                    if ob and ob[0] == FLIP[oa[0]]:
                        hits.append((oa[0], ob[0], b))
                        break
    if hits:
        print("### %-50s %4.1f%%  %d flipped branch(es)" % (e["name"].split("::")[-1],
                                                            float(e["matching"]) * 100, len(hits)))
        for o, n, ctx in hits[:3]:
            print("    orig %-4s ours %-4s %s" % (o, n, ctx.strip()[:90]))

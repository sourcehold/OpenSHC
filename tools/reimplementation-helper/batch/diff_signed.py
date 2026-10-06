"""Find comparisons the original makes signed and we make unsigned (or the reverse).

usage: diff_signed.py [NAME-SUBSTRING]

`jg/jge/jl/jle` against our `ja/jae/jb/jbe` (or the other way round) over the same `cmp` is a
signedness difference, not a different comparison: the field or local is `uint`/`undefined4` in the
generated header while the original treats it as `int`. Fix it in the source by comparing through
`(int)`, not by changing the generated header, and re-run this tool to confirm the pair is gone -
one instruction barely moves the percentage.

The counterpart tools are `diff_jcc.py` (strictness steps and flipped operands) and `diff_types.py`
(`movsx`/`movzx` and sign errors in formulas).
"""

import re
import sys

import common

JCC = re.compile(r"^(j[a-z]+)\s")
SIGNED = {"jg": "ja", "jge": "jae", "jl": "jb", "jle": "jbe"}
PAIRS = set()
for s, u in SIGNED.items():
    PAIRS.add((s, u))
    PAIRS.add((u, s))

want = sys.argv[1] if len(sys.argv) > 1 else ""


def stream(entry):
    out = []
    for hunk in entry.get("diff") or []:
        for block in hunk[1]:
            for kind, rows in block.items():
                for row in rows:
                    text = row[1]
                    src = text.split("\t")[1].strip() if "\t" in text else ""
                    out.append((kind, text.split("\t")[0].strip(), src))
    return out


total = 0
for f, e, address in common.entries(common.load_diff()):
    if e is None or (want and want not in e["name"]) or not e.get("diff"):
        continue
    rows = stream(e)
    hits = []
    for i in range(len(rows) - 1):
        k1, a, _ = rows[i]
        k2, c, src = rows[i + 1]
        if k1 != "orig" or k2 != "recomp":
            continue
        ja, jc = JCC.match(a), JCC.match(c)
        if ja and jc and (ja.group(1), jc.group(1)) in PAIRS:
            hits.append(("SIGN orig %-4s / ours %-4s" % (ja.group(1), jc.group(1)), src, i))
    if not hits:
        continue
    total += len(hits)
    print("### %s %.1f%%" % (e["name"].split("::")[-1], float(e["matching"]) * 100))
    for tag, src, i in hits:
        print("  %-30s %s" % (tag, src))
        for j in range(max(0, i - 3), i):
            kind, text, ann = rows[j]
            print("      %-7s %-58s %s" % (kind, text[:58], ann))
print("\n%d signedness pair(s)" % total)

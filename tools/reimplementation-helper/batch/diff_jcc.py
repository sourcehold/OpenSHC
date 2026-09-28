"""Find comparisons whose operator or operand order is one step off the original.

usage: diff_jcc.py [NAME-SUBSTRING]

Reports two kinds of pair, each with the four preceding instructions so the
site can be found in the source:

  JCC   the two sides differ by one strictness step (jl/jle, jg/jge, ja/jae)
        or are direction-flipped (jl/jge).  A strictness step is a real
        off-by-one in the source: write the literal and operator the original
        shows, e.g. `cmp x,0xa0; jle` is `x <= 160`, not `x < 160`.
  CMP   the same two operands compared the other way round; swap the sides of
        the comparison in the source.

This has found genuine bugs where Ghidra's decompilation was wrong, so confirm
a fix by re-running this tool and checking the pair is gone - the match
percentage barely moves for a single instruction and tells you nothing.

Two pairs it reports are NOT source bugs, so check the context before editing:
  * `orig jl / ours jge` where both sides share the `cmp` is block placement,
    not an operator - the original puts the if-body out of line and jumps to
    it.  Fix that by moving the cold case last in the source, not by flipping
    the test.
  * `orig jns / ours jge` right after an `and` is the same thing twice; the
    `and` clears OF so the two encodings are equivalent.
"""

import re
import sys

import common

JCC = re.compile(r"^(j[a-z]+)\s")
CMP = re.compile(r"^cmp (.+?), (.+)$")
STEP = {("jl", "jle"), ("jle", "jl"), ("jg", "jge"), ("jge", "jg"),
        ("ja", "jae"), ("jae", "ja"), ("jb", "jbe"), ("jbe", "jb"),
        ("jl", "jge"), ("jge", "jl"), ("jg", "jle"), ("jle", "jg")}

want = sys.argv[1] if len(sys.argv) > 1 else ""


def stream(entry):
    """Interleaved (kind, text, source-annotation) in emission order.

    Pairing an `orig` line with the `recomp` line that immediately follows it is
    the only sound comparison; indexing `block['orig'][i]` against
    `block['recomp'][i]` invents pairs out of unrelated instructions.
    """
    out = []
    for hunk in entry.get("diff") or []:
        for block in hunk[1]:
            for kind, rows in block.items():
                for row in rows:
                    text = row[1]
                    src = text.split("\t")[1].strip() if "\t" in text else ""
                    out.append((kind, text.split("\t")[0].strip(), src))
    return out


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
        if ja and jc and (ja.group(1), jc.group(1)) in STEP:
            hits.append(("JCC  orig %-4s / ours %-4s" % (ja.group(1), jc.group(1)), src, i))
            continue
        ma, mc = CMP.match(a), CMP.match(c)
        if ma and mc and ma.group(1).strip() == mc.group(2).strip() and ma.group(2).strip() == mc.group(1).strip():
            hits.append(('CMP  orig "%s" / ours "%s"' % (a, c), src, i))
    if not hits:
        continue
    print("### %s %.1f%%" % (e["name"].split("::")[-1], float(e["matching"]) * 100))
    for tag, src, i in hits:
        print("  %-38s %s" % (tag, src))
        for j in range(max(0, i - 4), i):
            kind, text, ann = rows[j]
            print("      %-7s %-58s %s" % (kind, text[:58], ann))

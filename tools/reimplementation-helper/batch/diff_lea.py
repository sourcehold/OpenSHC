"""Find `lea` on our side where the original has a destructive `add`: a snapshot local we keep and
the original does not. Per function in cmake/openshc-sources.txt.local.

usage: diff_lea.py [--run] [NAME-SUBSTRING]

`field = snapshotLocal + delta` has to preserve the snapshot, so MSVC computes the sum into a third
register:

    lea ecx, [eax + ebp]          ; ours - ebp still holds the snapshot
    mov dword ptr [ebx], ecx

`field = field + delta` lets it update the register that already caches the field read, which is one
byte shorter and clobbers it:

    add ebp, eax                  ; the original
    mov dword ptr [ebx], ebp

The two forms are identical in behaviour whenever nothing between the read and the use writes that
field, which is the condition to check before removing the local. This was the whole remaining gap of
`updatePopularity`: six sites of

    int popularityAfterFear = this->playerDataArray[playerID].popularity;
    ...
    this->playerDataArray[playerID].popularity = popularityAfterFear + siegePenalty;

93.9% -> 100% once the local went, because the six extra bytes also put every later jump offset out
by six. Mind that a sibling line in the same function kept its local and still matched - the original
really does take a second snapshot there - so decide per site from the `lea`/`add` in the original
rather than from the shape of the neighbouring code.

LEA is reported when the original's `add reg, reg` and our `lea reg, [reg + reg]` pair up inside one
reccmp block and the register operands match as a set; RLEA is the reverse (the original keeps a
value we clobber), which means a local is *missing*. Instructions are paired inside one replacement
block and only when both sides have the same number of that kind of line, like `diff_types.py` - once
the streams drift the n-th line is no longer the same instruction. Confirm every hit against
`reccmp_report.py diff` before editing.

--run re-runs reccmp first (otherwise reccmp/dll/diff.json from the last run is used).
"""

import re
import sys

import common

REG = r"e[abcd]x|e[sd]i|e[sb]p"
ADD_RE = re.compile(r"^add (%s), (%s)$" % (REG, REG))
LEA_RE = re.compile(r"^lea (%s), \[(%s) \+ (%s)\]$" % (REG, REG, REG))


def op(line):
    return line.split("\t")[0].strip()


def blocks(entry):
    """[(orig_ops, recomp_ops)] per replacement block."""
    pairs = []
    for hunk in entry.get("diff") or []:
        for block in hunk[1]:
            o = [op(r[1]) for r in block.get("orig", [])]
            r = [op(r[1]) for r in block.get("recomp", [])]
            if o and r:
                pairs.append((o, r))
    return pairs


def hints_for(entry):
    hits = []

    def add(cls, a, b):
        if (cls, a, b) not in hits and len(hits) < 25:
            hits.append((cls, a, b))

    for o, r in blocks(entry):
        for cls, adds, leas in (("LEA", o, r), ("RLEA", r, o)):
            a = [x for x in adds if ADD_RE.match(x)]
            b = [x for x in leas if LEA_RE.match(x)]
            if not a or len(a) != len(b):
                continue
            for x, y in zip(a, b):
                ma, mb = ADD_RE.match(x), LEA_RE.match(y)
                # the sum's operands have to be the same two registers; only the destination differs
                if {ma.group(1), ma.group(2)} == {mb.group(2), mb.group(3)} and mb.group(1) not in {
                        mb.group(2), mb.group(3)}:
                    add(cls, x if cls == "LEA" else y, y if cls == "LEA" else x)
    return hits


def main():
    args = sys.argv[1:]
    if args and args[0] == "--run":
        common.run_reccmp()
        args = args[1:]
    want = args[0] if args else ""
    byaddr = common.load_diff()
    shown = total = 0
    for f, e, a in common.entries(byaddr):
        if e is None or float(e["matching"]) >= 1 or want not in e["name"]:
            continue
        total += 1
        hits = hints_for(e)
        if not hits:
            continue
        shown += 1
        print("### %s %.1f%% norm %.1f%%"
              % (e["name"], float(e["matching"]) * 100, common.normalized_ratio(e) * 100))
        for cls, x, y in hits:
            if cls == "LEA":
                print("  LEA      orig: %-30s ours: %-30s  drop the snapshot local" % (x, y))
            else:
                print("  RLEA     orig: %-30s ours: %-30s  the original keeps a local" % (x, y))
    if not total:
        print("nothing below 100% in the current list")
    else:
        print("\n%d of %d function(s) below 100%% have a lea/add hint" % (shown, total))


if __name__ == "__main__":
    main()

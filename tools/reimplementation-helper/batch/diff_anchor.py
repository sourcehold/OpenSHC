"""Find functions whose struct/loop base anchor differs from the original's.

usage: diff_anchor.py [--run] [NAME-SUBSTRING]

MSVC bases a run of accesses into one object on a single address and expresses every field as a
displacement off it:

    lea esi, [ecx + 0x367e4]      ; the anchor
    cmp dword ptr [esi - 0x201c], ebp
    mov dword ptr [esi + 0xe0], -1

Which field lands at offset 0 is MSVC's choice, and when it picks a different one than the original
did, *every* displacement in the function differs while the opcodes still line up. That reads as
allocator noise in the diff and is the single most expensive mismatch in this codebase: the anchor
alone is the whole gap between 83.7% and 61.7% on `processFoodConsumption`.

ANCHOR reports the two base constants and their difference, which is the distance between the two
fields MSVC chose. Look that offset up in the struct header to see which field the original anchored
on; the decompilation names it directly, as the pointer it starts the loop with
(`_playerData = &DAT_GameState.playerDataArray[1].foodClockSpeed`).

What to do about a hit, in the order that has paid:

1. Check whether a *recent source change* caused it. The anchor moves when a field loses stores - a
   local for a repeatedly stored field, or an LTCG-enabled CSE, both do it. Such a change can be
   correct and still cost 20 points; keep the form with the matching anchor and record why.
2. Otherwise the anchor is probably not reachable. Tested and ineffective on `updateCrowding`,
   `processFoodConsumption` and `processPeasantSpawnAndDespawnCycle`: the global vs `this->` spelling
   of any field, an extra read of the anchor field, casts on the index, declaration and statement
   order, `PlayerData*` pointer locals, and even an `int*` local pointing straight at the field the
   original anchors on - MSVC re-bases to the store target regardless.

An exception worth knowing: where a condition reads two arrays of the *same* struct, reaching the
second off a pointer to the first does move the base, and took `showPopAndGoldPopup` and
`createStatsPopUpEntities` from 87-89% to 100%. See the cheat sheet.

--run re-runs reccmp first (otherwise reccmp/dll/diff.json from the last run is used).
"""

import re
import sys

import common

# `lea esi, [ecx + 0x367e4]`, `add esi, 0x367e4`, `lea ebx, [eax + ebp]` is not an anchor
ANCHOR_RE = re.compile(r"^(?:lea (e[a-z]{2}), \[(e[a-z]{2}) \+ (0x[0-9a-f]{4,}|\d{4,})\]"
                       r"|add (e[a-z]{2}), (0x[0-9a-f]{4,}|\d{4,}))$")
MIN_ANCHOR = 0x1000


def op(line):
    return line.split("\t")[0].strip()


def anchors(lines):
    """[(register, constant)] for every base set-up in order."""
    out = []
    for line in lines:
        m = ANCHOR_RE.match(line)
        if not m:
            continue
        reg = m.group(1) or m.group(4)
        value = int(m.group(3) or m.group(5), 0)
        if value >= MIN_ANCHOR:
            out.append((reg, value))
    return out


def blocks(entry):
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
    for o, r in blocks(entry):
        a, b = anchors(o), anchors(r)
        if not a or len(a) != len(b):
            continue
        for (_, x), (_, y) in zip(a, b):
            if x != y and (x, y) not in [(h[0], h[1]) for h in hits]:
                hits.append((x, y, y - x))
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
        for x, y, delta in hits:
            print("  ANCHOR   orig: 0x%-8x ours: 0x%-8x ours is 0x%x %s - look that offset up in the "
                  "struct header" % (x, y, abs(delta), "higher" if delta > 0 else "lower"))
    if not total:
        print("nothing below 100% in the current list")
    else:
        print("\n%d of %d function(s) below 100%% anchor differently" % (shown, total))


if __name__ == "__main__":
    main()

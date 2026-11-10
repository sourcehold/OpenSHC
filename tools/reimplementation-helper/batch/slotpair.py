"""Recover the original<->ours stack-slot permutation from the aligned instruction streams.

usage: slotpair.py FILE.cpp

Use this when `diff_slots.py` says both sides touch the same number of `[esp + N]` slots but with
different access counts per slot: the set of locals is then right and only their order is wrong, which
shifts every displacement in the function and reads as a large mismatch while the code is correct.

The obvious way to compare the two frames is to track `esp` from the function entry across every
`push`/`pop`/`sub esp`/`add esp`. That drifts in any function that pushes call arguments and lets a
`__stdcall` or `__thiscall` callee pop them, which is most of them. This script needs no depth tracking
at all: wherever the two instruction streams are *aligned* the stack depth is the same on both sides -
same frame, same prologue pushes, same argument pushes - so for a `-`/`+` pair of otherwise identical
instructions the difference of the two `[esp + N]` displacements is exactly the difference of the two
entry-relative slot offsets.

It reads a `quick_diff.py -s` diff of the file, pairs each `-` line with the `+` line that matches it
once displacements are blanked, and reports every `(original, ours)` displacement pair with that delta
and how often it occurs. A delta of +4 on one pair and -4 on another is two adjacent slots exchanged.

The limit is that a *displacement* only names a slot relative to a depth, so the same `[esp + 0x2c]` at
two different argument depths names two different locals and shows up as two pairs with different
deltas. Each delta is correct at its own site; what the output does not give you is one global
slot-to-slot map.

What to do with the answer: MSVC's stack colorer sorts by reference weight per byte, not by declaration
order (see IMPLEMENTATION_CHEAT_SHEET.md, "Variable Usage"), so declaration order decides only the
*ties*. Permuting declarations therefore pays exactly when two locals of equal weight sit in each
other's slots - that is what `perm_decls.py` and `quick_reorder.py -s` are for - and cannot move slots
whose weights differ. `applyAIV` is the worked negative case: this script shows its slots permuted by
+-4 and +-8, and thirteen variants including every declaration permutation measured tie-or-worse,
because its weights are not equal in the first place.
"""

import os
import re
import subprocess
import sys
from collections import Counter

import common

DISP = re.compile(r"\[esp \+ (0x[0-9a-f]+|\d+)\]")

if len(sys.argv) < 2:
    sys.exit(__doc__)
src = sys.argv[1]


def blank(text):
    return DISP.sub("[esp+?]", text)


def displacements(text):
    return [int(v, 0) for v in DISP.findall(text)]


def quick_diff_lines():
    cmd = [sys.executable, str(common.ROOT / "tools/reimplementation-helper/batch/quick_diff.py"),
           os.path.abspath(src), "-s"]
    env = dict(os.environ, QD_OUT=os.environ.get("QD_OUT", "slotpair"))
    r = subprocess.run(cmd, cwd=common.ROOT, env=env, capture_output=True, text=True)
    if r.returncode or not r.stdout.strip():
        sys.exit("quick_diff.py failed:\n" + (r.stderr or r.stdout))
    return r.stdout.splitlines()


def pair_hunks(lines):
    """Walk the diff and pair each `-` line with the `+` line it matches, displacements aside."""
    pairs = Counter()
    i = 0
    while i < len(lines):
        if not lines[i].startswith("-"):
            i += 1
            continue
        j = i
        while j < len(lines) and lines[j].startswith("-"):
            j += 1
        k = j
        while k < len(lines) and lines[k].startswith("+"):
            k += 1
        plus = lines[j:k]
        taken = set()
        for minus in lines[i:j]:
            for index, candidate in enumerate(plus):
                if index in taken or blank(minus[1:]) != blank(candidate[1:]):
                    continue
                a, b = displacements(minus[1:]), displacements(candidate[1:])
                if len(a) == len(b):
                    for x, y in zip(a, b):
                        if x != y:
                            pairs[(x, y)] += 1
                taken.add(index)
                break
        i = k if k > i else i + 1
    return pairs


lines = quick_diff_lines()
if lines:
    print(lines[0])
pairs = pair_hunks(lines)
if not pairs:
    print("no slot displacement differs in an otherwise matching instruction - "
          "the frames agree, look elsewhere")
    sys.exit(0)
print("original   ours     delta (= orig_slot - ours_slot)   sites")
for (a, b), count in sorted(pairs.items()):
    print("  0x%02x  ->  0x%02x     %+5d                         x%d" % (a, b, a - b, count))

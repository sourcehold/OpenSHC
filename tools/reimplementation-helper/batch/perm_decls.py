"""Permute a short run of declarations and keep the order that matches best.

Declaration order does not decide stack slots: the colorer sorts its elements by reference weight
per byte (`StkColorCmp`, see the cheat sheet) and leaves only the *ties* to the order the symbols
arrive in. So this pays exactly when two locals of equal weight are declared the wrong way round -
they then sit in each other's slots and usually in each other's registers too, a mismatch that
spreads over every instruction touching either of them while `diff_triage.py` still reports the
function as register-naming only. Run `slot_weight.py` first: if the weights differ, no permutation
of the declarations will move those slots. `assignSelectionToKey` had the original's slot *set* exactly
(`0x18`, `0x1c`, `0x20`) with `tribeIndex` and `slotID` swapped between `0x18` and `0x20`;
declaring `tribeIndex` first took it from 95.9% to 100%.

Find the candidates with `diff_slots.py`: same number of slots on both sides but a different
use count per slot. Then read the original's spill order - `mov [esp+0x18], edi` before
`mov [esp+0x20], esi` means the local in the lower slot is declared first.

This permutes every order of one run and scores with `quick_diff.py -s` (stack offsets kept, which
is what makes slot assignment visible), so a run of four costs about two minutes. It only moves
whole statements and only within the run, and an order that does not compile scores -1 and is
rejected - but it does not check data dependencies, so read `git diff` before keeping the result.
Confirm the winner with `reccmp_report.py --run`.

usage:
  perm_decls.py FILE.cpp FIRST_SUBSTRING LAST_SUBSTRING
"""

import itertools
import re
import subprocess
import sys
from pathlib import Path

import common

QUICK_DIFF = Path(__file__).resolve().parent / "quick_diff.py"
MAX_STATEMENTS = 6


def group_statements(lines):
    """Split lines into whole statements by bracket balance."""
    out, current, balance = [], [], 0
    for line in lines:
        current.append(line)
        balance += line.count("(") - line.count(")") + line.count("{") - line.count("}")
        if balance == 0:
            out.append("".join(current))
            current = []
    if current:
        out.append("".join(current))
    return out


def main():
    if len(sys.argv) != 4:
        sys.exit(__doc__)
    path = Path(common.repo_relative(sys.argv[1]))
    first, last = sys.argv[2], sys.argv[3]
    original = path.read_text(encoding="utf-8")
    lines = original.splitlines(True)

    try:
        start = next(i for i, l in enumerate(lines) if first in l)
        end = next(i for i, l in enumerate(lines) if last in l and i >= start)
    except StopIteration:
        sys.exit("could not find the run: %r .. %r" % (first, last))

    head, tail = "".join(lines[:start]), "".join(lines[end + 1:])
    statements = group_statements(lines[start:end + 1])
    if len(statements) > MAX_STATEMENTS:
        sys.exit("%d statements in the run; %d is the most this permutes"
                 % (len(statements), MAX_STATEMENTS))

    def score(order):
        common.write_text(path, head + "".join(order) + tail)
        out = subprocess.run([sys.executable, str(QUICK_DIFF), path.as_posix(), "-q", "-s"],
                             capture_output=True, text=True).stdout
        found = re.search(r"ratio ([0-9.]+)", out)
        return float(found.group(1)) if found else -1.0

    best, best_order = score(statements), list(statements)
    print("%d statements, base %.4f" % (len(statements), best))
    try:
        for order in itertools.permutations(statements):
            if list(order) == statements:
                continue
            ratio = score(list(order))
            if ratio > best + 1e-9:
                best, best_order = ratio, list(order)
                print("  %.4f  %s" % (ratio, " | ".join(s.strip().splitlines()[0][:44] for s in order)))
    finally:
        common.write_text(path, head + "".join(best_order) + tail)
    print("best %.4f, left in the file (check git diff, then reccmp_report.py --run)" % best)
    return 0


if __name__ == "__main__":
    sys.exit(main())

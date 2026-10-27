"""Split each function's remaining gap into register naming and real structure.

reccmp compares instruction text, so which register MSVC picked for `this` cascades
into every instruction that touches it. playUnitCombatSpeechForTarget is the clear
case: its prologue differs only in `mov ebx, ecx` against our `mov edi, ecx`, and
from there almost nothing lines up - 31.0% raw against 65.5% once the register names
are taken out.

This re-scores every function with the general-purpose register names replaced by one
token, leaving esp alone because stack references are meaningful.

  blind >> raw   the mismatch is mostly which register holds what. Not reachable from
                 the source; isTribePathToDestinationClear (18.8 -> 68.5) and
                 createAnimal (46.8 -> 82.0) are both in this group, which is why
                 every structural change tried on them measured flat or worse.
  blind ~= raw   the instructions really differ. Worth reading the diff.

"reach" is the instruction count that differs even register-blind, so it ranks what
is actually worth attacking - unlike rank_functions.py, which ranks by total loss and
sends you at the register-bound ones first.

usage: diff_regalloc.py [--by-name]
"""

import difflib
import re
import sys

import common

REG = re.compile(r"\b(?:e?(?:ax|bx|cx|dx|si|di|bp)|[abcd][lh]|sil|dil|bpl)\b")


def blind(line):
    return REG.sub("R", common._normalize(line))


def main():
    by_name = "--by-name" in sys.argv[1:]
    rows = []
    for f, e, a in common.entries(common.load_diff()):
        if not e or float(e["matching"]) >= 1.0:
            continue
        orig, recomp = common._asm_lines(e)
        if not orig:
            continue
        b = difflib.SequenceMatcher(
            None, [blind(x) for x in orig], [blind(x) for x in recomp],
            autojunk=False).ratio()
        raw = float(e["matching"])
        rows.append((len(orig) * (1 - b), len(orig) * (1 - raw), raw * 100,
                     b * 100, e["name"].split("::")[-1]))
    rows.sort(key=(lambda r: r[4]) if by_name else (lambda r: -r[0]))
    print("%7s %7s %6s %6s  %s" % ("reach", "lost", "raw", "blind", "function"))
    for reach, lost, raw, b, name in rows:
        print("%7.0f %7.0f %6.1f %6.1f  %s" % (reach, lost, raw, b, name))
    print("\n%d function(s). reach = instructions that differ even register-blind."
          % len(rows))


main()

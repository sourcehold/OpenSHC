"""Did FgEarlyTailDup duplicate the function's tail block, and if not, which test failed?

usage: taildup_probe.py FILE.cpp --invocation N        (N from slot_probe.py --find LOCAL)

`FgEarlyTailDup` (c2.dll 0x10b2bad0, called first thing in GlobalRegAlloc when optimising for
speed) looks at ONE block: the one immediately before the exit block. It copies that block's
tuples into every predecessor - which is where the original's inline `xor eax, eax / ret`
early-exit epilogues come from - when all of these hold:

  * the block starts with a label (it is a jump target, i.e. a shared return)
  * it has at most 2 real tuples, none a call (kind 0xf), an __asm tuple, or a branch at the end
  * no predecessor ends in a switch/computed jump (kind 0x14)
  * predecessors * tuples <= 8   (4 when not optimising for speed)

So a cold `return FALSE` shared by up to four guards is duplicated only if it is the LAST block
in source order before the function's exit - which is what diff_triage.py's "ret positions
differ" means, and why `goto fail; ... fail: return FALSE;` at the end can fix a function.

Prints, for the invocation: TAIL ntuples, PREDS n, and DUP when the copy happened; nothing
after TAIL means a predecessor test or the budget rejected it.
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import slot_probe
from slot_probe import EQ, NL, GLOBAL_REG_ALLOC, run

ENTRY = '0x10b2bad0'
AFTER_COUNT = '0x10b2bbcc'      # ebx = real tuples in the tail block
AFTER_PREDS = '0x10b2bc6f'      # edi = predecessors
DUP = '0x10b2bc92'              # the copy loop is entered


def probe(src, invocation):
    lines = ['sxe ld:c2', 'g',
             'bp1 ' + ENTRY + ' ".printf ' + EQ + 'ETD enter' + NL + EQ + '; gc"',
             'bp2 ' + AFTER_COUNT + ' ".printf ' + EQ + 'TAIL %d' + NL + EQ + ', @ebx; gc"',
             'bp3 ' + AFTER_PREDS + ' ".printf ' + EQ + 'PREDS %d' + NL + EQ + ', @edi; gc"',
             'bp4 ' + DUP + ' ".printf ' + EQ + 'DUP' + NL + EQ + '; gc"',
             'bp5 0x10b2bb10 ".printf ' + EQ + 'STAGE exit-tuple ok' + NL + EQ + '; gc"',
             'bp6 0x10b2bb41 ".printf ' + EQ + 'STAGE tail starts with a label' + NL + EQ + '; gc"',
             'bp7 0x10b2bb5d ".printf ' + EQ + 'STAGE tail end is not a branch/call' + NL + EQ + '; gc"',
             'bp8 0x10b2bb97 ".printf ' + EQ + 'STAGE tuple kind=%x op=%x' + NL + EQ + ', @ecx & 0xff, poi(@eax+4); gc"',
             'bd 1-8', 'r $t0=0',
             'bp0 ' + GLOBAL_REG_ALLOC + ' "r $t0=@$t0+1; .if (@$t0==0n' + str(invocation) +
             ') { be 1-8 }; .if (@$t0==0n' + str(invocation + 1) + ') { bd 1-8 }; gc"',
             'g', 'q', '']
    txt = run(lines, src, 'taildup-%s-%d' % (os.path.basename(src)[:-4], invocation))
    return [l for l in txt.splitlines() if re.match(r'^(ETD|TAIL|PREDS|DUP|STAGE)', l)]


if __name__ == '__main__':
    argv = [a for a in sys.argv[1:] if not a.startswith('--')]
    inv = None
    for i, a in enumerate(sys.argv):
        if a == '--invocation' and i + 1 < len(sys.argv):
            inv = int(sys.argv[i + 1]); argv = [x for x in argv if x != sys.argv[i + 1]]
    if not argv or inv is None:
        sys.exit(__doc__)
    for l in probe(argv[0], inv):
        print(l)
    print('(no TAIL line: the tail block did not start with a label or ended in a branch/call;'
          ' TAIL without PREDS: more than 2 tuples or a call/asm in it; PREDS without DUP: a'
          ' predecessor ends in a switch, or preds*tuples > 8)')

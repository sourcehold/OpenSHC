"""Compare the argument-push pattern of every call, original against ours.

usage: push_pattern.py FILE.cpp...

For each `call` the tool looks back over the instructions that set up its arguments and reports

    N/M   N pushes, M computing instructions interleaved between the first push and the call

A **neat** run (`M == 0`) means every argument was already in a register or a stack slot when the
push sequence started, i.e. the source had a **local** for it. A **mixed** run means the compiler
loaded or computed an argument in the middle of the pushes, which is what writing the expression
**inline at the call** produces. So where the two sides disagree:

    orig neat, ours mixed  ->  give that argument a local, computed before the call
    orig mixed, ours neat  ->  drop the local and write the expression in the call

`mov ecx, <this>` is ignored: it is the thiscall receiver, not an argument.

The call order has to line up for the comparison to mean anything, so the tool prints both columns
side by side and leaves the pairing to you; a `*` marks a row where the classification differs.
"""
import os
import re
import sys

import quick_diff

PUSH = re.compile(r'^push ')
THIS = re.compile(r'^mov ecx, (G|\[?\w)')


def runs(stream):
    """One entry per call: (pushes, interleaved, first_push_index)."""
    out = []
    for i, ins in enumerate(stream):
        if not ins.startswith('call'):
            continue
        j = i - 1
        pushes = interleaved = 0
        last_push = None
        # walk back while the window still looks like argument set-up
        while j >= 0:
            s = stream[j]
            if PUSH.match(s):
                pushes += 1
                last_push = j
                j -= 1
                continue
            if s.startswith(('call', 'ret', 'jmp')) or s.startswith('j'):
                break
            if pushes == 0:
                # computation after the last push but before the call still counts once a push follows
                j -= 1
                if j >= 0 and PUSH.match(stream[j]):
                    interleaved += 1
                    continue
                break
            if THIS.match(s):
                j -= 1
                continue
            interleaved += 1
            j -= 1
        if pushes:
            out.append((pushes, interleaved, last_push))
    return out


for f in sys.argv[1:]:
    a, b = quick_diff.streams(os.path.abspath(f))
    if b is None:
        continue
    ra, rb = runs(a), runs(b)
    print('##### %s   orig %d calls, ours %d calls' % (os.path.basename(f), len(ra), len(rb)))
    print('      %-22s %-22s' % ('original', 'ours'))
    for k in range(max(len(ra), len(rb))):
        pa = '%d/%d' % ra[k][:2] if k < len(ra) else '-'
        pb = '%d/%d' % rb[k][:2] if k < len(rb) else '-'
        mark = ''
        if k < len(ra) and k < len(rb):
            neat_a, neat_b = ra[k][1] == 0, rb[k][1] == 0
            mark = '*' if neat_a != neat_b else ''
        ca = a[ra[k][2]:][:1] if k < len(ra) else ['']
        print('%4d  %-22s %-22s %s %s' % (k, pa, pb, mark, ca[0] if ca else ''))

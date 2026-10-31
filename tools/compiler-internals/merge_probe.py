"""Did MSVC merge blocks in THIS function? The discriminator for a POLARITY report.

usage: merge_probe.py FILE.cpp --invocation N          merge attempts/outcomes for that function
       merge_probe.py FILE.cpp [FILE2.cpp ...]          whole translation unit (noisy)

`structural_diff.py` reports POLARITY when the original branches the other way round, and the
advice is to swap the arms. That is right when the two sides genuinely differ in source shape,
and wrong when the flip is MSVC having merged two blocks the original left separate - the arms
are then already correct and swapping them cannot help, because the merge happens in the late
flow optimisations, *after* register allocation, on whatever the allocator made identical. Those
two cases look identical in the diff. This tells them apart.

Decoded from c2.dll (addresses are c2.pdb publics, see pdbnames.py):

* Two merge families run for us, both driven from `@FgDoLateFlowOptsOnce@20` (and again from
  `@FgTryEpilogMerge@20`):
    - pairwise:      `@FgTryTailMerge@16`        0x10b2e1b0, exits `mov eax,1` 0x10b2e6e5 (merged)
                                                              and `xor eax,eax` 0x10b2e6f7 (declined)
    - common tail:   `@FgTryCommonTailMerge@8`   0x10b306c0 -> `@FgDoCommonTailMerge@20` 0x10b307e0,
                     whose exits are `mov eax,1` 0x10b30d73 (merged) and `xor eax,eax` 0x10b30833
                     (declined)
  `@FgTryHeadMerge@16` / `@FgCompareMerge@12` are the head-merge counterpart and are counted
  at their entries only. `@FgTailMergeWithoutCheck@8` is a per-instruction predicate, not an
  action, and is not counted.
* Every one of these routines opens with `cmp dword ptr [_PogoFlag], 1` and returns 0 on the
  `== 1` side. So `_PogoFlag == 1` (PGO instrumentation, which must keep blocks intact for its
  counters) disables block merging entirely; in a build without a profile - every build here -
  all of it is live. An earlier reading of FgCompareMerge as having the opposite polarity was
  wrong and is corrected here. The script prints the flag so this is checked on every run.
* Both merge families have to be counted. `renderMultilineTextUnk` showed 20 pairwise attempts
  all declined while the common-tail path merged - a tool reading FgTryTailMerge alone would
  have called it "no merge".

Per-function attribution uses the same trick as reg_scores.py: the 12 phases run per function,
so everything between `dop2_GlobalRegAlloc` invocation N and N+1 belongs to function N, and the
late flow optimisations fall in that window. Get N from `reg_scores.py FILE --find LOCAL` **in
the same session** - it depends on the translation unit's template population, which changes
with the resolver state and the compile command (renderMultilineTextUnk was #37 under one
configuration and #74 under another).

The counts are exact for one function with --invocation. Without it they cover the whole
translation unit, where hundreds of resolver templates merge among themselves; those numbers
are only meaningful as a *difference between two variants of the same file*, where the
template noise cancels. That controlled difference is the decisive instrument: countOccupied-
PlayerSlots' else-if variant showed exactly +4 pairwise merges over the || variant - one per
unrolled body - and nothing else moved.

Reading the result: attempts with zero merged in both families means every candidate pair was
rejected, so a POLARITY report is a real source-shape difference - swap the arms. Merges > 0
means blocks were folded together after allocation and the polarity may be a downstream effect;
confirm with a two-variant difference before spending time on the arms.
"""

import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                '..', 'reimplementation-helper', 'batch'))
import common

CDB = r"C:\Program Files (x86)\Windows Kits\10\Debuggers\x86\cdb.exe"
GLOBAL_REG_ALLOC = '0x10c07350'   # @dop2_GlobalRegAlloc@4
POGO_FLAG = '0x10d0ffdc'          # _PogoFlag

# (event name, address). Exits are inside the routine, so they are only reached from it.
EVENTS = [
    ('pair_attempt',    '0x10b2e1b0'),  # @FgTryTailMerge@16 entry
    ('pair_merged',     '0x10b2e6e5'),  #   mov eax, 1
    ('pair_declined',   '0x10b2e6f7'),  #   xor eax, eax
    ('common_attempt',  '0x10b307e0'),  # @FgDoCommonTailMerge@20 entry (via FgTryCommonTailMerge)
    ('common_merged',   '0x10b30d73'),  #   mov eax, 1
    ('common_declined', '0x10b30833'),  #   xor eax, eax
    ('head_attempt',    '0x10b2eb00'),  # @FgTryHeadMerge@16 entry
    ('head_compare',    '0x10b2f700'),  # @FgCompareMerge@12 entry
    ('epilog_attempt',  '0x10b321e0'),  # @FgTryEpilogMerge@20 entry
]

out = (common.ROOT / common.TMP / 'mergeprobe').resolve()
out.mkdir(parents=True, exist_ok=True)
BS = chr(92)
Q = chr(34)
EQ = BS + Q                 # an escaped quote, for a string nested inside a bp command
NL = BS + BS + 'n'


def compile_command(src):
    cc = json.loads(common.read_text(common.BUILD_DIR / 'compile_commands.json'))
    ours = [e for e in cc if 'OpenSHC.dll.dir' in e['command']
            and '/src/OpenSHC/' in e['file'].replace('\\', '/')]
    if not ours:
        sys.exit('configure the build first: no OpenSHC.dll entry in compile_commands.json')
    o = str(out).replace('\\', '/')
    cmd = re.sub(r'/Fo\S+', lambda _m: '/Fo%s/r.obj' % o, ours[0]['command'])
    cmd = re.sub(r'-c \S+$', lambda _m: '-c ' + os.path.abspath(src), cmd)
    return cmd, ours[0]['directory']


def run(lines, src, tag):
    path = out / (tag + '.cdb')
    common.write_text(path, '\r\n'.join(lines) + '\r\n')
    cmd, cwd = compile_command(src)
    env = common.build_env()
    env['PATH'] = str(common.ROOT / 'MSVC1400-SP1' / 'Common7' / 'IDE') + os.pathsep + env['PATH']
    full = '"%s" -cf "%s" %s' % (CDB, path, cmd)
    r = subprocess.run(full, cwd=cwd, env=env, capture_output=True, text=True, timeout=3600)
    common.write_text(out / (tag + '.log'), r.stdout)
    return r.stdout


def probe(src, invocation=None):
    # Each breakpoint prints a NUMERIC event id. cdb -cf echoes every script line, so a textual
    # tag would be counted once in the echoed `bp` command itself; "EV %d" cannot match "EV 3".
    bps = []
    for i, (_name, addr) in enumerate(EVENTS, start=1):
        bps.append('bp%d %s ".printf %sEV %%d%s%s, 0n%d; gc"' % (i, addr, EQ, NL, EQ, i))
    last = len(EVENTS)
    lines = ['sxe ld:c2', 'g',
             '.printf ' + Q + 'POGOFLAG %d' + NL + Q + ', poi(' + POGO_FLAG + ')']
    lines += bps
    if invocation is not None:
        lines += ['bd 1-%d' % last, 'r $t0=0',
                  'bp0 ' + GLOBAL_REG_ALLOC + ' "r $t0=@$t0+1; .if (@$t0==0n' + str(invocation) +
                  ') { be 1-%d }; .if (@$t0==0n' % last + str(invocation + 1) + ') { bd 1-%d }; gc"' % last]
    lines += ['g', 'q', '']
    tag = 'merge-%s-%s' % (os.path.basename(src), invocation if invocation is not None else 'all')
    txt = run(lines, src, tag)
    if 'Malformed' in txt:
        sys.exit('cdb rejected a breakpoint command - see ' + str(out / (tag + '.log')))
    counts = {}
    for m in re.finditer(r'^EV (\d+)\s*$', txt, re.M):
        i = int(m.group(1))
        if 1 <= i <= len(EVENTS):
            name = EVENTS[i - 1][0]
            counts[name] = counts.get(name, 0) + 1
    fl = re.search(r'POGOFLAG (-?\d+)', txt)
    return (fl.group(1) if fl else '?'), counts


def report(src, invocation):
    flag, c = probe(src, invocation)

    def g(k):
        return c.get(k, 0)

    scope = ('GlobalRegAlloc invocation %d' % invocation) if invocation is not None \
        else 'whole translation unit'
    print('### %s   (%s)' % (os.path.basename(src), scope))
    print('  _PogoFlag        %s   %s' % (
        flag, 'block merging is DISABLED (PGO instrumentation mode)' if flag == '1'
        else 'block merging is live'))
    print('  pairwise  FgTryTailMerge       attempts %4d   merged %4d   declined %4d'
          % (g('pair_attempt'), g('pair_merged'), g('pair_declined')))
    print('  common    FgDoCommonTailMerge  attempts %4d   merged %4d   declined %4d'
          % (g('common_attempt'), g('common_merged'), g('common_declined')))
    print('  head      FgTryHeadMerge       attempts %4d   (FgCompareMerge %d, FgTryEpilogMerge %d)'
          % (g('head_attempt'), g('head_compare'), g('epilog_attempt')))
    merged = g('pair_merged') + g('common_merged')
    attempts = g('pair_attempt') + g('common_attempt')
    print('  MERGES PERFORMED %d' % merged)
    if attempts and not merged:
        print('')
        print('  Every candidate pair was rejected, so a POLARITY report for this function is a')
        print('  real source-shape difference: swap the arms and invert the test.')
    elif merged:
        print('')
        print('  Blocks were folded together after allocation. A POLARITY report here may be a')
        print('  downstream effect; confirm with a two-variant difference before touching the arms.')
    return c


if __name__ == '__main__':
    inv = None
    rest = []
    it = iter(sys.argv[1:])
    for a in it:
        if a.startswith('--invocation='):
            inv = a.split('=', 1)[1]
        elif a == '--invocation':
            inv = next(it, None)
        elif not a.startswith('--'):
            rest.append(a)
    if not rest:
        sys.exit(__doc__)
    for p in rest:
        report(p, int(inv) if inv else None)
        print('')

"""Dump every global register candidate at each stage of c2's `Color`, for one function.

usage: color_probe.py FILE.cpp --name FUNC [--shift N] [--watch ID]
       color_probe.py --compare A.txt B.txt

Built to explain why one function compiles differently when only the TU's symbol count changes
(msvc-backend.md, "The TU symbol count decides some register choices"): run it on the committed
file and again with `--shift N` (N dummy `typedef short` lines prepended to a temporary copy, the
same thing shift_sweep.py does), then `--compare` the two outputs. Candidates are matched by
symbol id and name, so the comparison shows which fields differ, not just that the numbers moved.

Output lines (saved to the probe folder as color-<FILE>-<FUNC>-<shift>.txt and printed):

  CK <stage> cls=<class mask>      checkpoint; every candidate follows as a G line
  G <stage> num id key c24 c28 c2c c40 c38 f4 L<base:b1:b2>.. N=name
                                   num  +0x1c candidate number (the order the greedy passes walk)
                                   id   +0x44 symbol id (the colouring tie-break)
                                   key  +0x0c colouring key, c40 +0x40 spill benefit, c24 +0x24
                                        reference count, f4 +0x04 flags (byte +5 bit 4 = never fold)
  FV num id f5 ..                  FoldTooCheapDefs looks at a candidate (number order)
  FK1 / FK2 <eax>                  its two veto tests (ComponentKilled, the def check)
  FOLD num id                      ...and folds it into its uses (DoFoldDef)
  SPILL num id c24 c40 N=name      SpillObvious spills it (number order)
  SUBST num id N=name              ...and substitutes its def
  SERVE / SOD / HCU num id key c40 colouring pops it / SpillOrDefer / HandleCurrUncolorable
  CPR id legal=..                  ChoosePhysReg is asked for it
  CPRDONE id reg=.. w=..           ...and chose that register (1 eax .. 8 edi) with these weights
  WATCH / FLAGW                    with --watch ID: who writes that candidate's flag byte +5

Stages: 0 before SubsumeGlobregs, 1 after it, 2 after FoldTooCheapDefs, 3 after
InitialSplitPoints, 4 after Spillcosts, 5 after SpillObvious, 6 after OrderGlobregs, 7/8 the
re-split round (before Spillcosts / after SpillObvious), 9 class done.
"""

import collections
import os
import re
import sys

import c2base
from slot_probe import EQ, NL, GLOBAL_REG_ALLOC, COLOR_ENTRY, run, name_test, out

GLOBREG_HASH = '0x10d15090'   # _GlobregHash: 0x400 chains, bucket = number & 0x3ff, next at +0x30
STAGES = [
    ('0x10b0d0a5', 0),        # before SubsumeGlobregs
    ('0x10b0d0aa', 1),        # after SubsumeGlobregs
    ('0x10b0d0bf', 2),        # after FoldTooCheapDefs + CreateBlockBvs
    ('0x10b0d149', 3),        # after InitialSplitPoints
    ('0x10b0d15a', 4),        # after Spillcosts
    ('0x10b0d169', 5),        # after SpillObvious
    ('0x10b0d22f', 6),        # after OrderGlobregs
    ('0x10b0d2ab', 7),        # re-split round: before Spillcosts
    ('0x10b0d2bf', 8),        # re-split round: after SpillObvious
    ('0x10b0d497', 9),        # class done
]

# one candidate per G line; run with $$>< so the whole walk is one command. $t9 = stage number
DUMP = (r'r $t1=0' '\n'
        r'.while (@$t1 < 0x400) { r $t2=poi(' + GLOBREG_HASH + r'+@$t1*4); .while (@$t2 != 0) { '
        r'.printf "G %x num=%x id=%x key=%d c24=%x c28=%x c2c=%x c40=%d c38=%x f4=%x ", @$t9, poi(@$t2+0x1c), '
        r'poi(@$t2+0x44), poi(@$t2+0xc), poi(@$t2+0x24), poi(@$t2+0x28), poi(@$t2+0x2c), poi(@$t2+0x40), '
        r'poi(@$t2+0x38), poi(@$t2+4); .if (poi(@$t2+0x20) != 0) { r $t3=poi(poi(@$t2+0x20)); .while (@$t3 != 0) '
        r'{ .printf "L%x:%x:%x ", poi(@$t3), poi(@$t3+4), poi(@$t3+8); r $t3=poi(@$t3+0xc) } }; r $t4=poi(@$t2); '
        r'.if (@$t4 != 0) { .if (poi(@$t4) != 0) { .if (poi(poi(@$t4)+4) != 0) { .printf "N=%ma", '
        r'poi(poi(@$t4)+4)+1 } } }; .printf "\n"; r $t2=poi(@$t2+0x30) }; r $t1=@$t1+1 }' '\n')

# the symbol name of the candidate in $t2, for the one-line breakpoints
NAME = ('r $t4=poi(@$t2); .if (@$t4 != 0) { .if (poi(@$t4) != 0) { .if (poi(poi(@$t4)+4) != 0) { .printf ' +
        EQ + 'N=%ma' + EQ + ', poi(poi(@$t4)+4)+1 } } }; .printf ' + EQ + NL + EQ)


def one(label, reg):
    return ('"r $t2=' + reg + '; .printf ' + EQ + label + ' num=%x id=%x key=%d c40=%d' + NL + EQ +
            ', poi(@$t2+0x1c), poi(@$t2+0x44), poi(@$t2+0xc), poi(@$t2+0x40); gc"')


def breakpoints(dump_path, watch):
    dp = str(dump_path).replace('\\', '/')
    bps = [(a, '"r $t9=0n%d; .printf ' % n + EQ + 'CK %d cls=%%x' % n + NL + EQ + ', @ebx; $$><' + dp + '; gc"')
           for a, n in STAGES]
    bps += [
        ('0x10b0d350', one('SERVE', '@ebp')),
        ('0x10b0d37e', one('SOD', '@ebp')),
        ('0x10b0d3c5', one('HCU', '@ebp')),
        ('0x10b0d471', '"r $t2=@ebp; .printf ' + EQ + 'CPR id=%x legal=%x/%x/%x' + NL + EQ +
         ', poi(@$t2+0x44), poi(poi(poi(@$t2+0x20))), poi(poi(poi(@$t2+0x20))+4), poi(poi(poi(@$t2+0x20))+8); gc"'),
        ('0x10b0d476', '"r $t2=@ebp; .printf ' + EQ + 'CPRDONE id=%x reg=%x w=%d,%d,%d,%d,%d,%d,%d,%d' + NL + EQ +
         ', poi(@$t2+0x44), (poi(@$t2+0x10)-0x10d09f70)/0x60, poi(0x10d14f14), poi(0x10d14f18), poi(0x10d14f1c), poi(0x10d14f20), '
         'poi(0x10d14f24), poi(0x10d14f28), poi(0x10d14f2c), poi(0x10d14f30); gc"'),
        # FoldTooCheapDefs phase 2 walks _GlobregHash in number order; esi = candidate
        ('0x10b0dd20', '"r $t2=@esi; .printf ' + EQ + 'FV num=%x id=%x f5=%x u14=%x def=%x defop=%x c34=%x' + NL +
         EQ + ', poi(@$t2+0x1c), poi(@$t2+0x44), by(@$t2+5), poi(@$t2+0x14), poi(@$t2+0x3c), '
         '(poi(@$t2+0x3c)!=0)*poi(poi(@$t2+0x3c)+4), by(@$t2+0x34); gc"'),
        ('0x10b0ddc5', '".printf ' + EQ + 'FK1 %x' + NL + EQ + ', @eax; gc"'),
        ('0x10b0dde4', '".printf ' + EQ + 'FK2 %x' + NL + EQ + ', @eax; gc"'),
        ('0x10b0de18', '"r $t2=@esi; .printf ' + EQ + 'FOLD num=%x id=%x' + NL + EQ +
         ', poi(@$t2+0x1c), poi(@$t2+0x44); gc"'),
        # SpillObvious: eax = the candidate at the Spill call and at the CmdSubstDef call
        ('0x10b115d6', '"r $t2=@eax; .printf ' + EQ + 'SPILL num=%x id=%x c24=%x c40=%d ' + EQ +
         ', poi(@$t2+0x1c), poi(@$t2+0x44), poi(@$t2+0x24), poi(@$t2+0x40); ' + NAME + '; gc"'),
        ('0x10b11630', '"r $t2=@eax; .printf ' + EQ + 'SUBST num=%x id=%x ' + EQ +
         ', poi(@$t2+0x1c), poi(@$t2+0x44); ' + NAME + '; gc"'),
    ]
    if watch is not None:
        # after SubsumeGlobregs: find the candidate with that symbol id, hardware-watch its flag byte
        bps.append(('0x10b0d0b0', '"r $t5=0; r $t1=0; .while (@$t1 < 0x400) { r $t2=poi(' + GLOBREG_HASH +
                    '+@$t1*4); .while (@$t2 != 0) { .if (poi(@$t2+0x44) == ' + watch + ') { r $t5=@$t2 }; '
                    'r $t2=poi(@$t2+0x30) }; r $t1=@$t1+1 }; .printf ' + EQ + 'WATCH %x f5=%x' + NL + EQ +
                    ', @$t5, by(@$t5+5); ba30 w1 @$t5+5 ' + EQ + '.echo FLAGW; ? by(@$t5+5); r eip; k 8; gc' +
                    EQ + '; gc"'))
    return bps


KEEP = re.compile(r'^(FOUND|CK|G |SERVE|SOD|CPR|HCU|COLORENTRY|FV|FK|FOLD|SPILL|SUBST|WATCH|FLAGW|Evaluate|eip=|'
                  r'[0-9a-f]{8} [0-9a-f]{8} )')


def probe(src, name, shift, watch):
    tag = 'color-%s-%s-%d' % (os.path.basename(src)[:-4], name, shift)
    dump = out / (tag + '.dump')
    dump.write_text(c2base.rebase(DUMP))
    bps = breakpoints(dump, watch)
    n = len(bps)
    gate = ('r $t7=poi(poi(@eax)+4); ' + name_test(name) + '; .if (@$t6 != 0) { .printf ' + EQ + 'FOUND' + NL +
            EQ + '; be 1-%d } .else { bd 1-%d }' % (n, n))
    lines = ['sxe ld:c2', 'g']
    lines += ['bp%d %s %s' % (i, a, c) for i, (a, c) in enumerate(bps, 1)]
    # Color runs again for the stack colouring (COLOR_ENTRY): stop logging there
    lines += ['bp%d %s ".printf ' % (n + 1, COLOR_ENTRY) + EQ + 'COLORENTRY' + NL + EQ + '; bd 1-%d; gc"' % n,
              'bd 1-%d' % n,
              'bp0 ' + GLOBAL_REG_ALLOC + ' "' + gate + '; gc"',
              'g', 'q', '']
    target = src
    if shift:
        # beside the original, so its relative #includes still resolve
        target = src[:-4] + '__colorpad%d.cpp' % shift
        pad = ''.join('typedef short ShiftPad%d;\n' % i for i in range(shift)).encode()
        open(target, 'wb').write(pad + open(src, 'rb').read())
    try:
        txt = run(lines, target, tag)
    finally:
        if shift:
            os.remove(target)
    if 'Malformed' in txt or 'Syntax error' in txt:
        sys.exit('cdb rejected a command - see ' + str(out / (tag + '.log')))
    if 'FOUND' not in txt:
        sys.exit('GlobalRegAlloc never ran for ?%s@ - check --name' % name)
    result = '\n'.join(l.rstrip() for l in txt.splitlines() if KEEP.match(l)) + '\n'
    (out / (tag + '.txt')).write_text(result)
    return result, out / (tag + '.txt')


REGS = dict(enumerate(['-', 'eax', 'ecx', 'edx', 'ebx', 'esp', 'ebp', 'esi', 'edi']))
EVENTS = ('FOLD', 'SPILL', 'SUBST', 'SERVE', 'CPRDONE')


def load(path):
    """-> ({(stage, occurrence): [candidate dicts]}, {event kind: [event dicts]}, num -> (id, name))"""
    stages, events, seen, cur = {}, collections.defaultdict(list), collections.Counter(), None
    for line in open(path):
        line = line.rstrip()
        if line.startswith('CK '):
            stage = int(line.split()[1])
            cur = stages.setdefault((stage, seen[stage]), [])
            seen[stage] += 1
        elif line.startswith('G ') and cur is not None:
            cur.append(dict(re.findall(r'(\w+)=(\S+)', line)))
        elif line.split(' ', 1)[0] in EVENTS:
            events[line.split(' ', 1)[0]].append(dict(re.findall(r'(\w+)=(\S+)', line)))
    return stages, events


def compare(pa, pb):
    """Per checkpoint, the candidates whose fields differ other than by their number; per kind of
    event, the sequence of symbols in both runs up to and past the first divergence."""
    (sa, ea), (sb, eb) = load(pa), load(pb)
    names = {}
    for stages in (sa, sb):
        for gs in stages.values():
            for d in gs:
                if d.get('N'):
                    names[d['id']] = d['N']

    def label(d):
        if 'num' not in d:   # CPRDONE carries the register instead
            r = int(d.get('reg', '0'), 16)
            return '%s%s=%s' % (d['id'], '(' + names[d['id']] + ')' if d['id'] in names else '', REGS.get(r, hex(r)))
        tail = '#' + d['num']
        return '%s%s%s' % (d['id'], '(' + names[d['id']] + ')' if d['id'] in names else '', tail)

    def by_symbol(gs):
        m = collections.defaultdict(list)
        for d in gs:
            m[d['id']].append((d['key'], d['c24'], d['c40'], d['f4'], int(d['num'], 16)))
        return {k: sorted(v) for k, v in m.items()}

    print('candidates per checkpoint, compared by symbol id (fields: key c24 c40 f4 #num)')
    for k in sorted(set(sa) | set(sb)):
        x, y = by_symbol(sa.get(k, [])), by_symbol(sb.get(k, []))
        diffs = [i for i in sorted(set(x) | set(y)) if [t[:4] for t in x.get(i, [])] != [t[:4] for t in y.get(i, [])]]
        print('CK %d.%d  candidates %d/%d  differing %d' % (k[0], k[1], len(sa.get(k, [])), len(sb.get(k, [])),
                                                         len(diffs)))
        for i in diffs[:12]:
            print('    id=%s %s\n       A %s\n       B %s' % (i, names.get(i, ''), x.get(i), y.get(i)))
    print('\nevent order, as symbol id(name)#number')
    for kind in EVENTS:
        la, lb = [label(d) for d in ea.get(kind, [])], [label(d) for d in eb.get(kind, [])]
        if [s.split('#')[0] for s in la] == [s.split('#')[0] for s in lb]:
            print('%-7s same order (%d)' % (kind, len(la)))
            continue
        print('%-7s A: %s\n        B: %s' % (kind, ' '.join(la), ' '.join(lb)))


def main():
    if '--compare' in sys.argv:
        i = sys.argv.index('--compare')
        compare(sys.argv[i + 1], sys.argv[i + 2])
        return
    if '--name' not in sys.argv:
        sys.exit(__doc__)
    src = os.path.abspath(sys.argv[1])
    name = sys.argv[sys.argv.index('--name') + 1]
    shift = int(sys.argv[sys.argv.index('--shift') + 1]) if '--shift' in sys.argv else 0
    watch = sys.argv[sys.argv.index('--watch') + 1] if '--watch' in sys.argv else None
    txt, path = probe(src, name, shift, watch)
    print(txt)
    print('saved to ' + str(path))


if __name__ == '__main__':
    main()

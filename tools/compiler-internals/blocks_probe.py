"""Dump a function's block list, with tuple kinds/opcodes, at the points that decide block layout.

usage: blocks_probe.py FILE.cpp --name FUNCSUBSTRING     (preferred: invocation numbers drift between runs)
       blocks_probe.py FILE.cpp --invocation N
       blocks_probe.py FILE.cpp --scan                   every invocation, both phases

Phases printed (all inside the GlobalRegAlloc N..N+1 window):
  PHASE regalloc-entry       the block order c2 starts allocation with
  CTM ...                    every FgDoCommonTailMerge call (0x10b307e0): its two tuple args
  TMWC a=.. b=..             FgTailMergeWithoutCheck (0x10b30d90): a's tail folded onto b
  LABEL into=..              the newlabel path (0x10b30c58): a label inserted mid-block
  PHASE after-merge          the block list after each successful fold (0x10b30d73)
  PHASE color                at ColorStackElements (after allocation and the late flow opts)

Block layout (from CollectStackElements / FgEarlyTailDup): Function (c2!Function, 0x10d0d700)
+8 -> list node whose [0] is the first block; block+0 next, +4 prev, +8 preds, +0x1c -> head node
whose [0] is the first tuple, +0x20 the end tuple (exclusive). Tuple+0 next, +4 opcode, +8 kind,
+9 flags, +0x10 prev, +0x1c a 16-bit field the merge code compares and stores (line number?).
Each tuple prints as kind/opcode@field16.
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from slot_probe import EQ, NL, GLOBAL_REG_ALLOC, COLOR_ENTRY, run

FUNCTION = '0x10d0d700'


def dump(tag):
    return ('.printf ' + EQ + 'PHASE ' + tag + NL + EQ + '; '
            'r $t3=poi(poi(' + FUNCTION + ')+8); r $t3=poi(@$t3); r $t4=0; '
            '.while ((@$t3!=0) & (@$t4<0n90)) { '
            '.printf ' + EQ + 'BLK %d %x prev=%x preds=%x first=%x/%x last=%x/%x :' + EQ + ', @$t4, @$t3, poi(@$t3+4), poi(@$t3+8), '
            'poi(poi(@$t3+0x1c)+8)&0xff, poi(poi(@$t3+0x1c)+4), poi(poi(@$t3+0x20)+8)&0xff, poi(poi(@$t3+0x20)+4); '
            'r $t5=poi(poi(@$t3+0x1c)); r $t6=0; '
            '.while ((@$t5!=0) & (@$t6<0n400) & (@$t5!=poi(@$t3+0x20))) { '
            '.printf ' + EQ + ' %x:%x/%x@%d' + EQ + ', @$t5, poi(@$t5+8)&0xff, poi(@$t5+4), poi(@$t5+0x1c)&0xffff; '
            'r $t5=poi(@$t5); r $t6=@$t6+1 }; '
            '.printf ' + EQ + NL + EQ + '; r $t3=poi(@$t3); r $t4=@$t4+1 }')


RAW = ('r $t3=poi(poi(' + FUNCTION + ')+8); r $t3=poi(@$t3); r $t4=0; '
       '.while ((@$t3!=0) & (@$t4<0n12)) { .printf ' + EQ + 'RAWBLK %d first' + NL + EQ + ', @$t4; dd poi(@$t3+0x1c) L10; '
       '.printf ' + EQ + 'RAWBLK %d last' + NL + EQ + ', @$t4; dd poi(@$t3+0x20) L10; r $t3=poi(@$t3); r $t4=@$t4+1 }')


def probe(src, invocation):
    lines = ['sxe ld:c2', 'g',
             'bp1 0x10b307e0 ".printf ' + EQ + 'CTM eax=%x edx=%x s=%x %x %x' + NL + EQ +
             ', @eax, @edx, poi(@esp+4), poi(@esp+8), poi(@esp+0xc); gc"',
             'bp2 0x10b30ac7 ".printf ' + EQ + 'TMWC-site1 a=%x b=%x' + NL + EQ + ', @eax, @edx; gc"',
             'bp7 0x10b30ae5 ".printf ' + EQ + 'TMWC-site2 a=%x b=%x' + NL + EQ + ', @eax, @edx; gc"',
             'bp8 0x10b307e3 "' + dump('before-merge') + '; gc"',
             'bp3 0x10b30c58 ".printf ' + EQ + 'LABEL into=%x cut=%x' + NL + EQ + ', @ebx, @edi; gc"',
             'bp4 0x10b30d73 "' + dump('after-merge') + '; gc"',
             'bp5 ' + COLOR_ENTRY + ' "' + dump('color') + '; gc"',
             'bp6 0x10c07351 "' + dump('regalloc-entry') + '; gc"',
             'bd 1-8', 'r $t0=0',
             'bp0 ' + GLOBAL_REG_ALLOC + ' "r $t0=@$t0+1; .if (@$t0==0n' + str(invocation) +
             ') { be 1-6 }; .if (@$t0==0n' + str(invocation + 1) + ') { bd 1-6 }; gc"',
             'g', 'q', '']
    txt = run(lines, src, 'blocks-%s-%d' % (os.path.basename(src)[:-4], invocation))
    if 'Malformed' in txt or 'Syntax error' in txt:
        sys.exit('cdb rejected a command - see the log')
    return [l for l in txt.splitlines() if re.match(r'^(PHASE|BLK|CTM|TMWC|LABEL|RAWBLK|[0-9a-f]{8}  )', l)]


def probe_named(src, name):
    """Same as probe(), but the window is chosen by the function's (mangled) name instead of an
    invocation number: GlobalRegAlloc invocation numbers are NOT stable across runs (433 and 425
    for the same file - function order depends on pointer values), so every probe that keys on
    a number can land on a neighbour. The name is read at GlobalRegAlloc entry from the Function
    record: eax -> symbol at +0, mangled name at poi(sym+4) ("?name@Class@...")."""
    # aliases do not expand inside a breakpoint command, so match the first 8 bytes of the
    # mangled name ("?" + function name) as two little-endian dwords instead
    import struct
    mangled = ('?' + name + '        ')[:8].encode('ascii')
    w0, w1 = struct.unpack('<II', mangled)
    gate = ('r $t7=poi(poi(@eax)+4); .if ((poi(@$t7)==0x%x) & (poi(@$t7+4)==0x%x)) { .printf ' % (w0, w1) + EQ + 'FOUND ' + NL + EQ +
            '; da @$t7 L60; be 1-8 } .else { bd 1-8 }')
    lines = ['sxe ld:c2', 'g',
             'bp1 0x10b307e0 ".printf ' + EQ + 'CTM eax=%x edx=%x s=%x %x %x' + NL + EQ +
             ', @eax, @edx, poi(@esp+4), poi(@esp+8), poi(@esp+0xc); gc"',
             'bp2 0x10b30ac7 ".printf ' + EQ + 'TMWC-site1 a=%x b=%x' + NL + EQ + ', @eax, @edx; gc"',
             'bp7 0x10b30ae5 ".printf ' + EQ + 'TMWC-site2 a=%x b=%x' + NL + EQ + ', @eax, @edx; gc"',
             'bp8 0x10b307e3 "' + dump('before-merge') + '; gc"',
             'bp3 0x10b30c58 ".printf ' + EQ + 'LABEL into=%x cut=%x' + NL + EQ + ', @ebx, @edi; gc"',
             'bp4 0x10b30d73 "' + dump('after-merge') + '; gc"',
             'bp5 ' + COLOR_ENTRY + ' "' + dump('color') + '; gc"',
             'bp6 0x10c07351 "' + dump('regalloc-entry') + '; gc"',
             'bd 1-8',
             'bp0 ' + GLOBAL_REG_ALLOC + ' "' + gate + '; gc"',
             'g', 'q', '']
    txt = run(lines, src, 'blocks-%s-%s' % (os.path.basename(src)[:-4], name))
    if 'Malformed' in txt or 'Syntax error' in txt:
        sys.exit('cdb rejected a command - see the log')
    return [l for l in txt.splitlines() if re.match(r'^(FOUND|PHASE|BLK|CTM|TMWC|LABEL)', l)]


PASSES = [('Color', '0x10b0cf40'), ('FgDoLateFlowOpts', '0x10b2c950'), ('FgDoLateFlowOptsOnce', '0x10b2ccf0'),
          ('FgTryEpilogMerge', '0x10b321e0'), ('FgAdjustJumpToExitGoto', '0x10b2d530'),
          ('FgPretendToRemoveExitGoto', '0x10b2c5a0'), ('MscFixOpexitGoto', '0x10b9fd50')]


def probe_passes(src, name):
    """Dump the stream at the entry of each pass in PASSES (name-gated like probe_named), to see
    which one first shows a change - e.g. the end copies of the return blocks."""
    import struct
    mangled = ('?' + name + '        ')[:8].encode('ascii')
    w0, w1 = struct.unpack('<II', mangled)
    n = len(PASSES)
    gate = ('r $t7=poi(poi(@eax)+4); .if ((poi(@$t7)==0x%x) & (poi(@$t7+4)==0x%x)) { .printf ' % (w0, w1) + EQ + 'FOUND' + NL + EQ +
            '; be 1-%d } .else { bd 1-%d }' % (n, n))
    lines = ['sxe ld:c2', 'g']
    for i, (pn, addr) in enumerate(PASSES):
        lines.append('bp%d %s "' % (i + 1, addr) + dump('entry ' + pn) + '; gc"')
    lines += ['bd 1-%d' % n, 'bp0 ' + GLOBAL_REG_ALLOC + ' "' + gate + '; gc"', 'g', 'q', '']
    txt = run(lines, src, 'passes-%s-%s' % (os.path.basename(src)[:-4], name))
    return [l for l in txt.splitlines() if re.match(r'^(FOUND|PHASE|BLK)', l)]


def scan(src):
    """Dump the block list at GlobalRegAlloc entry and at ColorStackElements for EVERY invocation,
    tagged INV n, to find a function by its shape (the inline-asm tuple is kind 0x16 opcode 0x2ce)."""
    lines = ['sxe ld:c2', 'g', 'r $t0=0',
             'bp0 ' + GLOBAL_REG_ALLOC + ' "r $t0=@$t0+1; .printf ' + EQ + 'INV %d' + NL + EQ + ', @$t0; ' + dump('regalloc-entry') + '; gc"',
             'bp5 ' + COLOR_ENTRY + ' ".printf ' + EQ + 'INV %d' + NL + EQ + ', @$t0; ' + dump('color') + '; gc"',
             'g', 'q', '']
    txt = run(lines, src, 'blockscan-%s' % os.path.basename(src)[:-4])
    return [l for l in txt.splitlines() if re.match(r'^(INV|PHASE|BLK)', l)]


if __name__ == '__main__':
    if '--passes' in sys.argv:
        i = sys.argv.index('--passes')
        for l in probe_passes([a for a in sys.argv[1:] if not a.startswith('--') and a != sys.argv[i + 1]][0], sys.argv[i + 1]):
            print(l)
        sys.exit(0)
    if '--name' in sys.argv:
        i = sys.argv.index('--name')
        for l in probe_named([a for a in sys.argv[1:] if not a.startswith('--') and a != sys.argv[i + 1]][0], sys.argv[i + 1]):
            print(l)
        sys.exit(0)
    if '--scan' in sys.argv:
        for l in scan([a for a in sys.argv[1:] if not a.startswith('--')][0]):
            print(l)
        sys.exit(0)
    argv = [a for a in sys.argv[1:] if not a.startswith('--')]
    inv = None
    for i, a in enumerate(sys.argv):
        if a == '--invocation' and i + 1 < len(sys.argv):
            inv = int(sys.argv[i + 1]); argv = [x for x in argv if x != sys.argv[i + 1]]
    if not argv or inv is None:
        sys.exit(__doc__)
    for l in probe(argv[0], inv):
        print(l)

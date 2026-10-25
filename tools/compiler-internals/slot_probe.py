"""Trace how c2 decides a function's stack slot order, for one GlobalRegAlloc invocation.

usage: slot_probe.py FILE.cpp --invocation N
       slot_probe.py FILE.cpp --find LOCALNAME      which invocation(s) hold that local

What it prints, and why each part matters (msvc-backend.md, "The slot tiebreak, decoded"):

* every `AddStackElement` (0x10be9190) call, in order, with the element's name, size, weight
  before the call, the caller, the tuple and opcode, and for an inline-asm tuple (opcode 0x2ce)
  whether the reference came from a nested set. `CollectStackElements` makes one call per operand
  reference while walking the tuple stream; the first call inserts the element by size, every
  later one adds 1 to its weight and moves it ahead of same-size elements with strictly lower
  weight. So the list ends up size ascending, weight descending, and among equal weights in the
  order the elements reached their final weight. An __asm block is a single tuple whose operand
  sets are: its def-set (locals it writes, iterated in name-hash order), its use-list (locals it
  reads, reverse order of first mention), and the def-set again - each symbol counts once per set.
* the `symStackElements` list at `ColorStackElements` (0x10beaef0) entry, head to tail. Without
  the sort (below) this IS the slot order: head at the highest address.
* whether `QSortColors` ran. It runs only for frames over 0x80 bytes or functions with a /GS
  buffer; the (class, weight*1000/size) key that slot_map.py models never applies to a small
  frame without an array.
* the colour records after the (optional) sort: size, weight, class byte, alignment.

The record array is `Colort` (poi(0x10d0fa9c)), its count `numOfColors` (poi(0x10d0fa98)), the
element list head `symStackElements` (poi(0x10d0fab0)); an element's symbol is at +0, its size at
+0x20, weight at +0x38, next at +0x30, and the symbol's name is `da poi(sym+4)+1`. c2.pdb names
all of these. name_rank.cpp is a ready-made input for ranking candidate local names.
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
GLOBAL_REG_ALLOC = '0x10c07350'
BEFORE_SORT = '0x10beb34f'
AFTER_SORT = '0x10beb354'
REC_BASE = '0x10d0fa9c'
REC_COUNT = '0x10d0fa98'
ELEM_HEAD = '0x10d0fab0'
ADD_STACK_ELEMENT = '0x10be9190'
COLOR_ENTRY = '0x10beaef0'

out = (common.ROOT / common.TMP / 'slotprobe').resolve()
out.mkdir(parents=True, exist_ok=True)
BS = chr(92)
Q = chr(34)
EQ = BS + Q
NL = BS + BS + 'n'


def compile_command(src, tag='r'):
    cc = json.loads(common.read_text(common.BUILD_DIR / 'compile_commands.json'))
    ours = [e for e in cc if 'OpenSHC.dll.dir' in e['command']
            and '/src/OpenSHC/' in e['file'].replace('\\', '/')]
    if not ours:
        sys.exit('configure the build first')
    o = str(out).replace('\\', '/')
    cmd = re.sub(r'/Fo\S+', lambda _m: '/Fo%s/%s.obj' % (o, tag), ours[0]['command'])   # one .obj per run, so runs can overlap
    cmd = re.sub(r'-c \S+$', lambda _m: '-c ' + os.path.abspath(src), cmd)
    return cmd, ours[0]['directory']


def run(lines, src, tag):
    path = out / (tag + '.cdb')
    common.write_text(path, '\r\n'.join(lines) + '\r\n')
    cmd, cwd = compile_command(src, tag)
    env = common.build_env()
    env['PATH'] = str(common.ROOT / 'MSVC1400-SP1' / 'Common7' / 'IDE') + os.pathsep + env['PATH']
    full = '"%s" -cf "%s" %s' % (CDB, path, cmd)
    r = subprocess.run(full, cwd=cwd, env=env, capture_output=True, text=True, timeout=3600)
    common.write_text(out / (tag + '.log'), r.stdout)
    return r.stdout


NAME = ('.if (poi(@$t2) != 0) { .if (poi(poi(@$t2)+4) != 0) { da poi(poi(@$t2)+4)+1 L28 } .else { .printf '
        + EQ + '(temp)' + NL + EQ + ' } } .else { .printf ' + EQ + '(nosym)' + NL + EQ + ' }')


def dump_cmd(tag):
    # one line per colour record: REC <tag> idx size weight class align
    return ('r $t1=0; .while (@$t1 < poi(' + REC_COUNT + ')) { r $t2 = poi(' + REC_BASE + ') + @$t1*0n28; '
            '.printf ' + EQ + 'REC ' + tag + ' %d sz=%d wt=%d cls=%d al=%d' + NL + EQ +
            ', @$t1, poi(@$t2+8), poi(@$t2+0xc), (poi(@$t2+0x18) & 0xff), poi(@$t2+0x14); r $t1=@$t1+1 }')


def list_cmd():
    # the symStackElements list at ColorStackElements entry, head to tail: LIST idx elem size weight kind name
    return ('r $t2=poi(' + ELEM_HEAD + '); r $t1=0; .while (@$t2 != 0) { .printf ' + EQ +
            'LIST %d %x sz=%d wt=%d kind=%d ' + EQ + ', @$t1, @$t2, poi(@$t2+0x20), poi(@$t2+0x38), (poi(@$t2+4) & 0xff); '
            + NAME + '; r $t1=@$t1+1; r $t2=poi(@$t2+0x30) }')


def add_cmd():
    # every AddStackElement call: ADD elem size weight-before caller name
    return ('r $t2=@edx; .printf ' + EQ + 'ADD %x sz=%d wt=%d ret=%x tup=%x op=%x esi=%x edi=%x ' + EQ +
            ', @edx, poi(@edx+0x20), poi(@edx+0x38), poi(@esp), @ebx, poi(@ebx+4), @esi, @edi; ' + NAME)


ADD_RE = re.compile(r'^ADD ([0-9a-f]+) sz=(\d+) wt=(-?\d+) ret=([0-9a-f]+)(?: tup=([0-9a-f]+) op=([0-9a-f]+))?'
                    r'(?: esi=([0-9a-f]+) edi=([0-9a-f]+))? \s*(?:[0-9a-f]{8}\s+"([^"]*)"|\((temp|nosym)\))', re.M)
LIST_RE = re.compile(r'^LIST (\d+) ([0-9a-f]+) sz=(\d+) wt=(\d+) kind=(\d+) \s*(?:[0-9a-f]{8}\s+"([^"]*)"|\((temp|nosym)\))', re.M)


def parse(txt):
    """The ADD sequence and the final LIST of a probe log, as plain tuples."""
    adds = [(m.group(1), int(m.group(2)), int(m.group(3)), m.group(9) or m.group(10)) for m in ADD_RE.finditer(txt)]
    lst = [(m.group(2), int(m.group(3)), int(m.group(4)), m.group(6) or m.group(7)) for m in LIST_RE.finditer(txt)]
    return adds, lst, bool(re.search(r'^SORTED', txt, re.M))


def simulate(adds):
    """Replay AddStackElement (c2.dll 0x10be9190) over an ADD sequence of (elem, size, ...).

    First call for an element: insert it after every element whose size is <= its own, weight 1.
    Later calls: weight += 1, then move it forward past the same-size predecessors whose weight
    is strictly lower, stopping behind the first whose weight is >= the new one. Returns the
    list head-to-tail as [(elem, size, weight)]. test_slot_rules.py checks this against the
    recorded lists; slot_probe.py prints a mismatch if the live list ever disagrees.
    """
    order = []                        # elem ids head-to-tail
    size, weight = {}, {}
    for elem, sz in ((a[0], a[1]) for a in adds):
        if elem not in weight:
            size[elem], weight[elem] = sz, 1
            i = 0
            while i < len(order) and size[order[i]] <= sz:
                i += 1
            order.insert(i, elem)
            continue
        weight[elem] += 1
        i = order.index(elem)
        j = i
        while j > 0 and size[order[j - 1]] == sz and weight[order[j - 1]] < weight[elem]:
            j -= 1
        if j != i:
            order.pop(i)
            order.insert(j, elem)
    return [(e, size[e], weight[e]) for e in order]


def regime(frame, gs_buffer):
    """Does ColorStackElements sort the colours? Only for a frame over 0x80 bytes or a /GS
    buffer (Function+0xAC & 1); otherwise the element list order IS the slot order."""
    return 'sorted' if (frame > 0x80 or gs_buffer) else 'list-order'


def probe(src, invocation):
    lines = ['sxe ld:c2', 'g',
             'bp1 ' + ADD_STACK_ELEMENT + ' "' + add_cmd() + '; gc"',
             'bp2 ' + COLOR_ENTRY + ' "' + list_cmd() + '; gc"',
             'bp3 ' + BEFORE_SORT + ' ".printf ' + EQ + 'SORTED' + NL + EQ + '; gc"',
             'bp4 ' + AFTER_SORT + ' "' + dump_cmd('OUT') + '; gc"',
             'bd 1-4', 'r $t0=0',
             'bp0 ' + GLOBAL_REG_ALLOC + ' "r $t0=@$t0+1; .if (@$t0==0n' + str(invocation) +
             ') { be 1-4 }; .if (@$t0==0n' + str(invocation + 1) + ') { bd 1-4 }; gc"',
             'g', 'q', '']
    txt = run(lines, src, 'slots-%s-%d' % (os.path.basename(src)[:-4], invocation))
    if 'Malformed' in txt or 'Syntax error' in txt:
        sys.exit('cdb rejected a command - see ' + str(out))
    return txt


def find(src, name):
    """Which GlobalRegAlloc invocation(s) build a frame holding local NAME: the element list is
    dumped at ColorStackElements for every invocation, tagged with the invocation count."""
    lines = ['sxe ld:c2', 'g', 'r $t0=0',
             'bp0 ' + GLOBAL_REG_ALLOC + ' "r $t0=@$t0+1; gc"',
             'bp2 ' + COLOR_ENTRY + ' ".printf ' + EQ + 'INV %d' + NL + EQ + ', @$t0; ' + list_cmd() + '; gc"',
             'g', 'q', '']
    txt = run(lines, src, 'find-%s' % os.path.basename(src)[:-4])
    hits = []
    for block in re.split(r'^INV ', txt, flags=re.M)[1:]:
        inv = int(block.split(chr(10), 1)[0])
        names = re.findall(r'^LIST \d+ [0-9a-f]+ sz=\d+ wt=\d+ kind=\d+ \s*[0-9a-f]{8}\s+"([^"]*)"', block, re.M)
        if name in names:
            hits.append((inv, names))
    return hits


if __name__ == '__main__':
    argv = [a for a in sys.argv[1:] if not a.startswith('--')]
    inv = None
    for i, a in enumerate(sys.argv):
        if a == '--invocation' and i + 1 < len(sys.argv):
            inv = int(sys.argv[i + 1]); argv = [x for x in argv if x != sys.argv[i + 1]]
        elif a.startswith('--invocation='):
            inv = int(a.split('=', 1)[1])
    want = None
    for i, a in enumerate(sys.argv):
        if a == '--find' and i + 1 < len(sys.argv):
            want = sys.argv[i + 1]; argv = [x for x in argv if x != want]
    if argv and want:
        for inv, names in find(argv[0], want):
            print('invocation %d: %s' % (inv, ' '.join(names)))
        sys.exit(0)
    if not argv or inv is None:
        sys.exit(__doc__)
    txt = probe(argv[0], inv)
    name_re = r'(?:[0-9a-f]{8}\s+"([^"]*)"|\((temp|nosym)\))'
    print('### AddStackElement calls (walk order)')
    for m in re.finditer(r'^ADD ([0-9a-f]+) sz=(\d+) wt=(-?\d+) ret=([0-9a-f]+) tup=([0-9a-f]+) op=([0-9a-f]+) esi=([0-9a-f]+) edi=([0-9a-f]+) \s*' + name_re, txt, re.M):
        print('  %8s sz=%-3s wt=%-3s ret=%s tup=%8s op=%4s node=%8s outer=%8s  %s' % (m.group(1), m.group(2), m.group(3), m.group(4), m.group(5), m.group(6), m.group(7), m.group(8), m.group(9) or m.group(10)))
    print('### symStackElements at ColorStackElements entry (head to tail)')
    for m in re.finditer(r'^LIST (\d+) ([0-9a-f]+) sz=(\d+) wt=(\d+) kind=(\d+) \s*' + name_re, txt, re.M):
        print('  %3s %8s sz=%-3s wt=%-3s kind=%s  %s' % (m.group(1), m.group(2), m.group(3), m.group(4), m.group(5), m.group(6) or m.group(7)))
    adds, lst, sorted_ = parse(txt)
    predicted = [e for e, _s, _w in simulate(adds)]
    if predicted == [e for e, _s, _w, _n in lst]:
        print('### simulate() reproduces the recorded list (%d elements)' % len(lst))
    else:
        print('### simulate() DISAGREES with the recorded list - the rule in slot_probe.py is incomplete here')
    print('### QSortColors ran: %s' % ('yes' if sorted_ else 'NO (frame <= 0x80, no /GS buffer)'))
    print('### colour records after the (optional) sort')
    for m in re.finditer(r'^REC OUT (\d+) sz=(\d+) wt=(\d+) cls=(\d+) al=(\d+)', txt, re.M):
        print('  %3s sz=%-3s wt=%-3s cls=%s al=%s' % m.groups())

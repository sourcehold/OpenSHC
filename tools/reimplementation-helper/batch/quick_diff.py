"""Compile ONE source file and diff its code against the original function, in seconds.

usage: quick_diff.py FILE.cpp... [-q] [-s] [-r] [-l] [--runs N | --sbs [A-B]]

Compiles each file with a DLL compile command plus /FA (no link, no reccmp), disassembles the original function
at the file's `// FUNCTION:` address straight from `_original/` with capstone, normalizes both streams (globals,
call/jump targets and esp slots become tokens) and prints a difflib ratio and a unified diff (- original, + ours).
`-q` prints the ratio only; `-s` keeps `[esp + N]` offsets instead of collapsing them to one token, for chasing
stack-slot assignment (declaration order) once everything else matches.

For a large function whose gap is still structural, register names are noise that hides where the blocks
disagree. `-r` replaces every register with `R` before diffing (and prints that ratio as `reg`), `-l` tags each
of our lines with the source line it came from, `--runs N` lists only the mismatching runs of at least N lines
together with the source lines they cover - the list of places to work on, biggest first in practice - and
`--sbs A-B` prints the aligned streams side by side for original instructions A..B (all of them without a range),
our source line in the last column. All three imply `-r`.

This is a triage loop, not the score: it is stricter than reccmp about register names and looser about stack
offsets and constants, so confirm a 1.0000 with `reccmp_report.py --run`. Unlike reccmp it shows the *whole*
original function - reccmp cuts the original stream at the length of our function, which hides the original's
tail whenever ours is shorter. Needs capstone and a configured build directory. Do not run it while a build is
running: both write the same PDB.
"""
import difflib
import json
import os
import re
import subprocess
import sys

import capstone

import common

# set by main(); a module importing this one gets the defaults
keep_slots = False
ROOT = str(common.ROOT).replace(chr(92), '/')
os.chdir(ROOT)
ENV = common.build_env()
ENV['PATH'] = os.path.join(ROOT, 'MSVC1400-SP1', 'Common7', 'IDE') + os.pathsep + ENV['PATH']
cc = json.load(open('build-RelWithDebInfo/compile_commands.json'))
base = [e for e in cc if 'OpenSHC.dll.dir' in e['command'] and '/src/OpenSHC/' in e['file'].replace(chr(92), '/')][0]
# QD_OUT picks the output folder, so concurrent runs (quick_reorder.py) do not share x.asm
out = ROOT + '/build-RelWithDebInfo/batch/' + os.environ.get('QD_OUT', 'quick')
os.makedirs(out, exist_ok=True)

image = common.original_image()
d = image.data
off = image.off
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
REGISTER_RE = re.compile(r'\b(e?[abcd]x|[abcd][lh]|e?[sd]i|e?bp)\b')
# control flow of the last `orig()` / `ours()` result, one entry per instruction and parallel to it:
# orig_flow (address, branch target address or None), our_flow (labels defined here, branch target label or None),
# our_lines the source line each of our instructions came from
orig_flow = []
our_flow = []
our_lines = []


def num(m):
    v = int(m.group(0), 16) if m.group(0).lower().startswith('0x') else int(m.group(0))
    if v >= 0x80000000:
        return '-' + hex(0x100000000 - v)
    return 'G' if v >= 0x400000 else hex(v)


def orig(va):
    o = off(va)
    res = []
    prev = None
    end = va
    # function ends at first int3/padding after ret/jmp once no pending forward jump target lies beyond
    maxtarget = va
    del orig_flow[:]
    for i in md.disasm(d[o:o + 20000], va):
        if prev in ('ret', 'jmp') and i.address > maxtarget and (i.mnemonic in ('int3', 'nop') or i.address % 16 == 0 and i.mnemonic == 'int3'):
            break
        if prev in ('ret', 'jmp') and i.address > maxtarget:
            break
        s = i.mnemonic + ' ' + i.op_str
        target = None
        if i.mnemonic.startswith('j') or i.mnemonic == 'call':
            try:
                t = int(i.op_str, 16)
                if i.mnemonic != 'call' and va <= t < va + 20000:
                    maxtarget = max(maxtarget, t)
                    target = t
                    s = i.mnemonic + ' L'
                else:
                    s = i.mnemonic + ' F'
            except ValueError:
                pass
        else:
            s = re.sub(r'0x[0-9a-f]+|\b\d+\b', num, s)
            s = re.sub(r'(\w+) [+] G\b', r'\1 + G', s)
        if i.mnemonic == 'nop' or s.startswith('lea ') and re.match(r'lea (\w+), \[\1\]$', s) or s in ('mov edi, edi',):
            prev = prev
            continue
        res.append(s.strip())
        orig_flow.append((i.address, target))
        prev = i.mnemonic
    return res


def ours(f, cls, name):
    cmd = base['command']
    cmd = re.sub(r'/Fo\S+', lambda m: '/Fo' + out + '/x.obj /FA /Fa' + out + '/x.asm', cmd)
    cmd = re.sub(r'-c \S+$', lambda m: '-c ' + f, cmd)
    r = subprocess.run(cmd, cwd=base['directory'], env=ENV, capture_output=True, text=True)
    if r.returncode:
        print('\n'.join(l for l in r.stdout.splitlines() if 'error' in l) or r.stdout[-500:])
        return None
    txt = open(out + '/x.asm', errors='replace').read()
    m = re.search(r'^(\?%s@%s@\S+) PROC.*?\n(.*?)^\1 ENDP' % (name, cls), txt, re.S | re.M)
    if not m:
        print('no code found for %s::%s' % (cls, name))
        return None
    res = []
    # `_x$ = -16` lines define each local's offset; `_x$[esp+44H]` then means [esp + 0x44 - 16]
    pre = txt[txt.rfind('_TEXT	SEGMENT', 0, m.start()):m.start()]
    slots = {k: int(v) for k, v in re.findall(r'^(\w+\$\w*|tv\d+) = (-?\d+)', pre, re.M)}

    def slot(mm):
        base = slots.get(mm.group(1))
        off = (int(mm.group(2)[:-1], 16) if mm.group(2).endswith('H') else int(mm.group(2))) if mm.group(2) else 0
        # a hex offset keeps its sign in the first character: int('+1cH'[:-1], 16) handles it
        if base is None:
            return '[esp + ' + hex(off) + ']'
        v = base + off
        return '[esp + ' + hex(v) + ']' if v >= 0 else '[esp - ' + hex(-v) + ']'
    del our_lines[:]
    del our_flow[:]
    line = 0
    labels = []
    for l in m.group(2).splitlines():
        lm = re.match(r';\s*Line\s+(\d+)', l)
        if lm:
            line = int(lm.group(1))
            continue
        l = l.split(';')[0].strip()
        lab = re.match(r'^(\$\w+@\w+):', l)
        if lab:
            labels.append(lab.group(1))
            continue
        if not l or l.endswith(':') or re.match(r'^\w+\$\w* = ', l) or l.startswith('npad') or l.startswith('$') or l.startswith('DD') or l.startswith('DB') or l.startswith('_'):
            continue
        l = l.replace('\t', ' ')
        l = re.sub(r'(\w+\$\w*|tv\d+)\[esp(?:([+-][0-9a-fA-F]+H|[+-]\d+))?\]', slot, l)
        op = l.split(' ')[0]
        target = None
        if op.startswith('j') and 'DWORD PTR' not in l:
            mt = re.search(r'(\$\w+@\w+)', l)
            target = mt.group(1) if mt else None
            l = op + (' L' if '$' in l else ' F')
        elif op == 'call':
            l = 'call F'
        else:
            l = re.sub(r'OFFSET ', '', l)
            l = re.sub(r'\?[\w?$@]+', 'G', l)
            l = re.sub(r'_\w+\$\[', '[', l)
            l = re.sub(r'\b([0-9a-f]+)H\b', lambda m: hex(int(m.group(1), 16)), l)
            l = re.sub(r'(?<![\w])\d+\b', lambda m: hex(int(m.group(0))), l)
            l = l.replace('DWORD PTR', 'dword ptr').replace('WORD PTR', 'word ptr').replace('BYTE PTR', 'byte ptr')
            l = re.sub(r'G\[(.*?)\]', r'[\1+G]', l)
            l = re.sub(r'G\+0x[0-9a-f]+', 'G', l)
            l = re.sub(r'\[(.*?)\+G\+0x[0-9a-f]+\]', r'[\1+G]', l)
            l = re.sub(r'\[(.*?)\+0x[0-9a-f]+\+G\]', r'[\1+G]', l)
            l = re.sub(r'\[(.*?)\+G\]', r'[\1 + G]', l)
            l = re.sub(r'\[([^\]]*)\]', lambda m: '[' + re.sub(r'(?<=\w)([+-])(?=\w)', r' \1 ', m.group(1)) + ']', l)
            l = re.sub(r'ptr \[G\]', 'ptr [G]', l)
            l = re.sub(r'(dword|word|byte) ptr G\b', r'\1 ptr [G]', l)
            l = re.sub(r'^imul (\w+), (0x[0-9a-f]+|-?\d+)$', r'imul \1, \1, \2', l)
            l = re.sub(r'^lea (\w+), dword ptr ', r'lea \1, ', l)
        res.append(l.strip())
        our_lines.append(line)
        our_flow.append((labels, target))
        labels = []
    return res


def canon(s):
    # esp-relative slots and globals compare loosely
    if not keep_slots:
        s = re.sub(r'\[esp( [+-] 0x[0-9a-f]+)?\]', '[esp+N]', s)
    s = re.sub(r'tv\d+\[', '[', s)
    s = re.sub(r'_\w+\$\w*\[', '[', s)
    s = s.replace('mov eax, G', 'mov eax, 0x51eb851f') if s == 'mov eax, G' else s
    s = re.sub(r'\[(\w+)\*(\d) [+] G\]', r'[\1*\2 + G]', s)
    return s


def streams(f):
    """(original, ours) normalized instruction lists for one source file."""
    src = open(f, encoding='utf-8').read()
    va = int(re.search(r'FUNCTION: STRONGHOLDCRUSADER (0x[0-9A-Fa-f]+)', src).group(1), 16)
    cls, name = re.search(r'FUNCTION: STRONGHOLDCRUSADER[^\n]*\n[^\n(]*?(\w+)::(\w+)\(', src).groups()
    b = ours(f, cls, name)
    return [canon(x) for x in orig(va)], (None if b is None else [canon(x) for x in b])


def register_canon(lines):
    return [REGISTER_RE.sub('R', x) for x in lines]


def mismatch_runs(a, b, lines, min_size):
    """(op, orig range, ours range, source line range) for every non-equal run of at least min_size lines."""
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == 'equal' or (i2 - i1) + (j2 - j1) < min_size:
            continue
        src = sorted(set(l for l in lines[j1:j2] if l))
        if src:
            where = '%d-%d' % (src[0], src[-1])
        else:
            # nothing of ours here: name the line our code continues with
            where = 'near %d' % (lines[min(j1, len(lines) - 1)] if lines else 0)
        yield op, (i1, i2), (j1, j2), where


def side_by_side(a_raw, b_raw, a, b, lines, first, last):
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if i2 < first or i1 > last:
            continue
        for k in range(max(i2 - i1, j2 - j1)):
            x = a_raw[i1 + k] if i1 + k < i2 else ''
            y = b_raw[j1 + k] if j1 + k < j2 else ''
            ln = lines[j1 + k] if j1 + k < j2 else ''
            print('%-44s %s %-44s %s' % (x[:44], ' ' if op == 'equal' else '|', y[:44], ln))


def main():
    global keep_slots
    argv = sys.argv[1:]
    runs = sbs = None
    if '--runs' in argv:
        k = argv.index('--runs')
        runs = int(argv[k + 1])
        del argv[k:k + 2]
    if '--sbs' in argv:
        k = argv.index('--sbs')
        sbs = (0, 1 << 30)
        if k + 1 < len(argv) and re.match(r'^\d+-\d+$', argv[k + 1]):
            sbs = tuple(int(x) for x in argv[k + 1].split('-'))
            del argv[k + 1]
        del argv[k]
    flags = set(x for x in argv if x.startswith('-'))
    quiet = '-q' in flags
    keep_slots = '-s' in flags
    tag_lines = '-l' in flags
    reg = '-r' in flags or tag_lines or runs is not None or sbs is not None
    files = [os.path.abspath(f) for f in argv if not f.startswith('-')]
    if not files:
        sys.exit(__doc__)
    for f in files:
        a, b = streams(f)
        if b is None:
            continue
        ratio = difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()
        head = '##### %s  ratio %.4f' % (os.path.basename(f), ratio)
        ca, cb = a, b
        if reg:
            ca, cb = register_canon(a), register_canon(b)
            head += '  reg %.4f' % difflib.SequenceMatcher(None, ca, cb, autojunk=False).ratio()
        print(head + '  orig %d ours %d' % (len(a), len(b)))
        lines = list(our_lines)
        if runs is not None:
            for op, (i1, i2), (j1, j2), where in mismatch_runs(ca, cb, lines, runs):
                print('%-7s orig %5d-%-5d ours %5d-%-5d  src %s' % (op, i1, i2, j1, j2, where))
        elif sbs is not None:
            side_by_side(a, b, ca, cb, lines, sbs[0], sbs[1])
        elif not tag_lines:
            if not quiet:
                for l in difflib.unified_diff(ca, cb, lineterm='', n=2):
                    if not l.startswith(('---', '+++')):
                        print(l)
        elif not quiet:
            # diff the untagged lines (a tag would stop every moved line from matching), print tagged ones
            shown = ['%-40s @%d' % (x, n) for x, n in zip(cb, lines)]
            sm = difflib.SequenceMatcher(None, ca, cb, autojunk=False)
            for group in sm.get_grouped_opcodes(2):
                i1, j1 = group[0][1], group[0][3]
                i2, j2 = group[-1][2], group[-1][4]
                print('@@ -%d,%d +%d,%d @@' % (i1 + 1, i2 - i1, j1 + 1, j2 - j1))
                for op, a1, a2, b1, b2 in group:
                    if op == 'equal':
                        for x in ca[a1:a2]:
                            print(' ' + x)
                        continue
                    for x in ca[a1:a2]:
                        print('-' + x)
                    for x in shown[b1:b2]:
                        print('+' + x)


if __name__ == '__main__':
    main()

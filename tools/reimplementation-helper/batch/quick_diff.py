"""Compile ONE source file and diff its code against the original function, in seconds.

usage: quick_diff.py FILE.cpp... [-q] [-s]

Compiles each file with a DLL compile command plus /FA (no link, no reccmp), disassembles the original function
at the file's `// FUNCTION:` address straight from `_original/` with capstone, normalizes both streams (globals,
call/jump targets and esp slots become tokens) and prints a difflib ratio and a unified diff (- original, + ours).
`-q` prints the ratio only; `-s` keeps `[esp + N]` offsets instead of collapsing them to one token, for chasing
stack-slot assignment (declaration order) once everything else matches.

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
import struct
import subprocess
import sys

import capstone

import common

quiet = '-q' in sys.argv
keep_slots = '-s' in sys.argv
files = [os.path.abspath(f) for f in sys.argv[1:] if f not in ('-q', '-s')]
if not files and __name__ == "__main__":
    sys.exit(__doc__)
ROOT = str(common.ROOT).replace(chr(92), '/')
os.chdir(ROOT)
ENV = common.build_env()
ENV['PATH'] = os.path.join(ROOT, 'MSVC1400-SP1', 'Common7', 'IDE') + os.pathsep + ENV['PATH']
cc = json.load(open('build-RelWithDebInfo/compile_commands.json'))
base = [e for e in cc if 'OpenSHC.dll.dir' in e['command'] and '/src/OpenSHC/' in e['file'].replace(chr(92), '/')][0]
out = ROOT + '/build-RelWithDebInfo/batch/quick'
os.makedirs(out, exist_ok=True)

d = open('_original/Stronghold Crusader.exe', 'rb').read()
pe = struct.unpack_from('<I', d, 0x3c)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]
opt = struct.unpack_from('<H', d, pe + 20)[0]
ibase = struct.unpack_from('<I', d, pe + 24 + 28)[0]
secs = [struct.unpack_from('<IIII', d, pe + 24 + opt + 40 * i + 8) for i in range(nsec)]
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def off(va):
    r = va - ibase
    for vs, vaddr, rs, rp in secs:
        if vaddr <= r < vaddr + max(vs, rs):
            return r - vaddr + rp


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
    for i in md.disasm(d[o:o + 20000], va):
        if prev in ('ret', 'jmp') and i.address > maxtarget and (i.mnemonic in ('int3', 'nop') or i.address % 16 == 0 and i.mnemonic == 'int3'):
            break
        if prev in ('ret', 'jmp') and i.address > maxtarget:
            break
        s = i.mnemonic + ' ' + i.op_str
        if i.mnemonic.startswith('j') or i.mnemonic == 'call':
            try:
                t = int(i.op_str, 16)
                if i.mnemonic != 'call' and va <= t < va + 20000:
                    maxtarget = max(maxtarget, t)
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
    for l in m.group(2).splitlines():
        l = l.split(';')[0].strip()
        if not l or l.endswith(':') or re.match(r'^\w+\$\w* = ', l) or l.startswith('npad') or l.startswith('$') or l.startswith('DD') or l.startswith('DB') or l.startswith('_'):
            continue
        l = l.replace('\t', ' ')
        l = re.sub(r'(\w+\$\w*|tv\d+)\[esp(?:([+-][0-9a-fA-F]+H|[+-]\d+))?\]', slot, l)
        op = l.split(' ')[0]
        if op.startswith('j') and 'DWORD PTR' not in l:
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


def main():
    for f in files:
        a, b = streams(f)
        if b is None:
            continue
        ratio = difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()
        print('##### %s  ratio %.4f  orig %d ours %d' % (os.path.basename(f), ratio, len(a), len(b)))
        if not quiet:
            for l in difflib.unified_diff(a, b, lineterm='', n=2):
                if not l.startswith(('---', '+++')):
                    print(l)


if __name__ == '__main__':
    main()

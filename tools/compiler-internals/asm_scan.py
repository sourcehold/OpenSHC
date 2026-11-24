"""Find functions whose ORIGINAL contains handwritten inline assembly.

usage: asm_scan.py [SNAPSHOT.json] [SRCDIR ...]

Without arguments it scans every .cpp in cmake/openshc-sources.txt.local; with a reccmp_report.py
snapshot it scans only the functions below normalized 100 in it, and prints their percentages.

Why this exists: tracePathPlanToDestinationViaUnoccupiedTiles sat at 12.5% with a frame nine
locals short, and no C++ change could touch it, because the original's loop is an `__asm` block.
MSVC keeps an ebp frame in any function containing inline assembly, and every local the block
names has to live in memory - so the "missing locals" were the asm's operands, and the pragma
that gets the frame pointer (`optimize("y", off)`) gets nothing else. LinkageNeighbourAsm.hpp
documents the same discovery for three siblings. Such a function has to be written as asm,
instruction for instruction; tuning the C++ around it is wasted.

The fingerprints, each a thing MSVC's own codegen never emits:

  ebp   an ebp frame (push ebp / mov ebp, esp) WITHOUT the `and esp, -8` of stack alignment
  zx    `mov eax, 0` immediately followed by `mov ax, word ptr ...` (MSVC writes movzx)
  c16   16-bit register compares, `cmp ax, cx` and the like
  rld   layer bases reloaded from their own stack slot, `mov esi/edi, dword ptr [ebp - N]`
  al0   `cmp al/cl/dl, 0` (MSVC writes test)

The score is 3 for the frame plus 2 per zero-extension plus the others; anything scoring 3 or
more is listed. An ebp frame alone is also what `__asm`-free functions with a `double` or an
alloca get, so read the other columns before believing it. Over the 97 sub-100 PathFindingState
functions this listed exactly the four that are asm; the other 93 are ordinary C++ problems.
"""

import io
import json
import os
import re
import subprocess
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
MARK = re.compile(r'FUNCTION:\s*STRONGHOLDCRUSADER\s+(0x[0-9A-Fa-f]+)')


def original(addr):
    out = subprocess.run([sys.executable, 'tools/reimplementation-helper/batch/orig_body.py', addr],
                         cwd=ROOT, capture_output=True, text=True).stdout
    return [re.sub(r'^[0-9a-f]{8}\s+', '', l) for l in out.splitlines() if re.match(r'^[0-9a-f]{8}\s', l)]


def fingerprints(ins):
    n = len(ins)
    ebp = n > 2 and ins[0].startswith('push    ebp') and ins[1].startswith('mov     ebp, esp') \
        and not any('and     esp' in x for x in ins[:5])
    zx = sum(1 for i in range(n - 1) if re.match(r'mov\s+eax, 0$', ins[i]) and re.match(r'mov\s+ax,', ins[i + 1]))
    c16 = sum(1 for x in ins if re.match(r'cmp\s+[a-d]x, [a-d]x$', x))
    rld = sum(1 for x in ins if re.match(r'mov\s+(esi|edi), dword ptr \[ebp - 0x[0-9a-f]+\]$', x))
    al0 = sum(1 for x in ins if re.match(r'cmp\s+(al|cl|dl), 0$', x))
    score = (3 if ebp else 0) + zx * 2 + c16 + rld // 3 + al0
    return score, n, ebp, zx, c16, rld, al0


def main():
    args = sys.argv[1:]
    snap = None
    if args and args[0].endswith('.json'):
        snap = json.load(io.open(args[0], encoding='utf-8'))
        args = args[1:]
    files = []
    if args:
        for d in args:
            files += [os.path.join(d, f) for f in sorted(os.listdir(os.path.join(ROOT, d))) if f.endswith('.cpp')]
    else:
        files = [l.strip() for l in io.open(os.path.join(ROOT, 'cmake/openshc-sources.txt.local')) if l.strip()]
    pct = {}
    if snap is not None:
        for k, (raw, norm) in snap.items():
            pct[k.split('::')[-1]] = (100 * raw, 100 * norm)
    rows = []
    for p in files:
        short = os.path.basename(p)[:-4]
        if snap is not None and (short not in pct or pct[short][1] >= 99.95):
            continue
        m = MARK.search(io.open(os.path.join(ROOT, p), encoding='utf-8', errors='replace').read(4000))
        if not m:
            continue
        score, n, ebp, zx, c16, rld, al0 = fingerprints(original(m.group(1)))
        rows.append((score, pct.get(short, (0, 0)), short, n, ebp, zx, c16, rld, al0))
    rows.sort(reverse=True)
    print('%5s %5s %5s  %-52s %4s ebp zx c16 rld al0' % ('score', 'raw', 'norm', 'function', 'insn'))
    for score, (raw, norm), short, n, ebp, zx, c16, rld, al0 in rows:
        if score >= 3:
            print('%5d %5.1f %5.1f  %-52s %4d  %s  %2d %3d %3d %3d'
                  % (score, raw, norm, short[:52], n, 'Y' if ebp else '-', zx, c16, rld, al0))
    print('(%d function(s) scanned; listed: score >= 3)' % len(rows))


if __name__ == '__main__':
    main()

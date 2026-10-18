"""Hill-climb statement order inside named blocks, scored by quick_diff.py (seconds per trial, no build).

usage: quick_reorder.py FILE.cpp [-s] START END [START END ...]

Each START/END pair names a block: the statements from the first line containing START (searched after the
previous block) up to, but not including, the next line containing END. A statement is grouped by bracket
balance, so a multi-line declaration or a whole `if (...) { ... }` counts as one unit. Every unit is tried at
every other position of its block; a move is kept only when the quick_diff ratio strictly improves, and the
passes repeat until no move helps. The best version is left in the file (also on Ctrl+C or an error).

`-s` scores with stack offsets kept (quick_diff -s), which is what makes declaration order visible: slot
assignment and the callee-saved register each local gets both follow it. This took
`AICState::selectAttackTarget` from 68.8% to 100% with two declaration moves.

The script does NOT check data dependencies. A move that uses a variable before its declaration fails to
compile and is rejected, but moving a store across a read of the same field, or a side-effecting guard across
another one, compiles and can win. Only give it blocks of declarations and pure `return` guards, and read
`git diff` before keeping a result.

quick_diff writes build-RelWithDebInfo/batch/<QD_OUT>/x.asm (default `quick`); give concurrent runs their own
QD_OUT. A full build fails with C1033 while a run is compiling, so let runs finish before building.
"""
import os
import re
import subprocess
import sys
import time

QUICK_DIFF = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'quick_diff.py')

args = sys.argv[1:]
if not args:
    sys.exit(__doc__)
path = os.path.abspath(args.pop(0))
keep_slots = '-s' in args
args = [a for a in args if a != '-s']
if not args or len(args) % 2:
    sys.exit(__doc__)
pairs = [(args[i], args[i + 1]) for i in range(0, len(args), 2)]


def write(text):
    # an editor or virus scanner can briefly lock the file on Windows
    for _ in range(50):
        try:
            with open(path, 'w', encoding='utf-8', newline='') as fh:
                fh.write(text)
            return
        except OSError:
            time.sleep(0.5)
    raise OSError('cannot write ' + path)


def ratio():
    cmd = [sys.executable, QUICK_DIFF, path, '-q'] + (['-s'] if keep_slots else [])
    out = subprocess.run(cmd, capture_output=True, text=True).stdout
    m = re.search(r'ratio (\d\.\d+)', out)
    return float(m.group(1)) if m else -1.0


def units(lines):
    out, cur, depth = [], [], 0
    for line in lines:
        cur.append(line)
        depth += line.count('(') + line.count('{') - line.count(')') - line.count('}')
        stripped = line.strip()
        if depth == 0 and (stripped.endswith(';') or stripped.endswith('}') or not stripped):
            out.append(''.join(cur))
            cur = []
    if cur:
        out.append(''.join(cur))
    return out


def split(text):
    lines = text.splitlines(True)
    segments, pos = [], 0
    for start, end in pairs:
        i = next((k for k in range(pos, len(lines)) if start in lines[k]), None)
        if i is None:
            sys.exit('block start not found: %r' % start)
        j = next((k for k in range(i + 1, len(lines)) if end in lines[k]), None)
        if j is None:
            sys.exit('block end not found: %r' % end)
        segments.append(''.join(lines[pos:i]))
        segments.append(units(lines[i:j]))
        pos = j
    segments.append(''.join(lines[pos:]))
    return segments


def join(segments):
    return ''.join(s if isinstance(s, str) else ''.join(s) for s in segments)


segments = split(open(path, encoding='utf-8', newline='').read())
best = ratio()
print('start %.4f' % best, flush=True)
try:
    improved = True
    while improved:
        improved = False
        for index, block in enumerate(segments):
            if isinstance(block, str):
                continue
            for i in range(len(block)):
                if not block[i].strip():
                    continue
                for j in range(len(block)):
                    if j == i:
                        continue
                    trial_block = list(block)
                    unit = trial_block.pop(i)
                    trial_block.insert(j, unit)
                    trial = list(segments)
                    trial[index] = trial_block
                    write(join(trial))
                    score = ratio()
                    if score > best:
                        best, segments, block, improved = score, trial, trial_block, True
                        print('better %.4f: moved %r to %d' % (score, unit.strip()[:70], j), flush=True)
finally:
    write(join(segments))
print('final %.4f' % best)

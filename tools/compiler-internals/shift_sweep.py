"""Does a function's match depend on how many symbols its translation unit declares before it?

c2.dll numbers its global register candidates through a 64-bucket hash keyed on each global's
TU-wide symbol number (msvc-backend.md, "The TU symbol count decides some register choices"), so
a header edit anywhere above a function can move its match with no change to its source. This
tool compiles copies of a .cpp with N dummy `typedef short` lines prepended - each one shifts every
later symbol number by 1 - and records quick_diff's ratio per N.

usage: shift_sweep.py OUT.jsonl FILE.cpp [--name FUNC] [--shifts 0-63] [-j 14]
       shift_sweep.py OUT.jsonl --all [--shifts 0,17,34,51] [-j 14]    every // FUNCTION: in src/OpenSHC
       shift_sweep.py OUT.jsonl --only LIST.txt [--shifts ...]          LIST.txt lines: path<TAB>name
       shift_sweep.py OUT.jsonl --report                                 functions whose ratio varies

--shifts takes a comma list and/or ranges (`0-63`, `0,17,34,51`). OUT.jsonl is appended to and
resumable: (file, name, shift) triples already in it are skipped. The default for one file is the
whole period 0-63, for --all the 4-point screen 0,17,34,51 (cheap, but a function whose sensitive
window is narrower than 17 can slip through it).

Reading the report: `now` is shift 0 (the TU as committed), `best` the highest ratio over the
shifts measured and `at best` how many shifts reach it. A function whose best is 1.0 has the right
source - record it as "matches modulo TU symbol count" rather than padding the TU, because the
next header edit moves the count again. A function at 1.0 now with few shifts at best is fragile:
an unrelated header change can drop it.
"""

import json
import os
import re
import subprocess
import sys
import threading
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
QD = os.path.join(ROOT, 'tools', 'reimplementation-helper', 'batch', 'quick_diff.py')
MARK = re.compile(r'FUNCTION: STRONGHOLDCRUSADER (0x[0-9A-Fa-f]+)[^\n]*\n[^\n(]*?(?:(\w+)::)?(\w+)\(')
PAD = '__shiftpad'


def arg(flag, default=None):
    return sys.argv[sys.argv.index(flag) + 1] if flag in sys.argv else default


def parse_shifts(text):
    out = []
    for part in text.split(','):
        a, _, b = part.partition('-')
        out += range(int(a), int(b) + 1) if b else [int(a)]
    return out


def functions_in(path):
    src = open(os.path.join(ROOT, path), encoding='utf-8', errors='replace').read()
    return [m.group(3) for m in MARK.finditer(src)]


def targets():
    if '--only' in sys.argv:
        for line in open(arg('--only'), encoding='utf-8'):
            if line.strip():
                p, n = line.rstrip('\n').split('\t')
                yield p, n
        return
    if '--all' in sys.argv:
        for d, _, fs in os.walk(os.path.join(ROOT, 'src', 'OpenSHC')):
            for f in sorted(fs):
                if f.endswith('.cpp') and PAD not in f:
                    p = os.path.relpath(os.path.join(d, f), ROOT).replace('\\', '/')
                    for n in functions_in(p):
                        yield p, n
        return
    p = os.path.relpath(os.path.abspath(sys.argv[2]), ROOT).replace('\\', '/')
    names = functions_in(p)
    want = arg('--name')
    for n in names:
        if want is None or n == want:
            yield p, n
            if want is None:
                return


def report(out_path):
    runs = {}
    for line in open(out_path, encoding='utf-8'):
        r = json.loads(line)
        if 'ratio' in r:
            runs.setdefault((r['file'], r['name']), {})[r['shift']] = r['ratio']
    rows = []
    for (f, n), by in runs.items():
        vals = set(by.values())
        if len(vals) > 1:
            best = max(vals)
            rows.append((n, by.get(0), best, sum(v == best for v in by.values()), len(by),
                         [s for s in sorted(by) if by[s] == best]))
    print('%d functions measured, %d vary with the symbol count' % (len(runs), len(rows)))
    for n, now, best, k, total, good in sorted(rows, key=lambda r: (r[1] or 0) - r[2]):
        print('%-60s now %s  best %.4f at %d/%d  %s' % (
            n, '%.4f' % now if now is not None else '  -   ', best, k, total, spans(good)))


def spans(xs):
    out, start = [], None
    for i, x in enumerate(xs):
        if start is None:
            start = x
        if i + 1 == len(xs) or xs[i + 1] != x + 1:
            out.append(str(start) if start == x else '%d-%d' % (start, x))
            start = None
    return ','.join(out)


def main():
    out_path = os.path.abspath(sys.argv[1])
    if '--report' in sys.argv:
        report(out_path)
        return
    default = '0,17,34,51' if ('--all' in sys.argv or '--only' in sys.argv) else '0-63'
    shifts = parse_shifts(arg('--shifts', default))
    jobs = int(arg('-j', '14'))

    done = set()
    if os.path.exists(out_path):
        for line in open(out_path, encoding='utf-8'):
            r = json.loads(line)
            done.add((r['file'], r['name'], r['shift']))
    lock = threading.Lock()
    slots = list(range(jobs))
    slot_lock = threading.Lock()

    def run(task):
        path, name, n, multi = task
        with slot_lock:
            slot = slots.pop()
        try:
            full = os.path.join(ROOT, path)
            src = open(full, 'rb').read()
            # beside the original, so its relative #includes still resolve
            tmp = full[:-4] + '%s%d_%d.cpp' % (PAD, n, slot)
            pad = ''.join('typedef short ShiftPad%d;\n' % i for i in range(n)).encode()
            open(tmp, 'wb').write(pad + src)
            try:
                cmd = [sys.executable, QD, tmp, '-q'] + (['--name', name] if multi else [])
                env = dict(os.environ, QD_OUT='shift%d' % slot)
                r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, env=env, timeout=600)
                o = r.stdout + r.stderr
            finally:
                os.remove(tmp)
            m = re.search(r'ratio (\S+)\s+orig (\d+) ours (\d+)', o)
            rec = {'file': path, 'name': name, 'shift': n}
            if m:
                rec.update(ratio=float(m.group(1)), orig=int(m.group(2)), ours=int(m.group(3)))
            else:
                rec['error'] = o.strip()[-300:]
            with lock:
                with open(out_path, 'a', encoding='utf-8') as fh:
                    fh.write(json.dumps(rec) + '\n')
        finally:
            with slot_lock:
                slots.append(slot)

    tl = list(targets())
    count = {}
    for p, n in tl:
        count[p] = len(functions_in(p))
    tasks = [(p, n, s, count[p] > 1) for p, n in tl for s in shifts if (p, n, s) not in done]
    print('%d functions, %d compiles to do' % (len(tl), len(tasks)), flush=True)
    with ThreadPoolExecutor(jobs) as ex:
        list(ex.map(run, tasks))
    report(out_path)


if __name__ == '__main__':
    main()

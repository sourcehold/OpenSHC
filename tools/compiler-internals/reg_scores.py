"""Print the register-candidate scores MSVC computes for one of our functions.

usage: reg_scores.py FILE.cpp --probe
       reg_scores.py FILE.cpp --find [LOCALNAME ...]
       reg_scores.py FILE.cpp --invocation N

`OrderGlobregs` scores every candidate value and orders them by descending score; `Color`
walks that order and `ChoosePhysReg` serves each from the still-available registers. So the
score decides *which* value gets a register, and this script reads the scores out of the
running compiler, with the candidates resolved back to source variable names.

It drives `cl.exe` under the x86 `cdb` with breakpoints taken from `c2.pdb`'s public
addresses - see msvc-backend.md for how that works and why no symbol loading is needed.

Two steps, because the compiler allocates for every function in the translation unit and
ours is not distinguishable by size (hundreds of resolver-template instantiations score
identically):

* `--probe` prints how many candidates each `GlobalRegAlloc` invocation inserted, biggest
  first. Our function is normally the largest, but only because the resolver templates all
  score identically (33 candidates in a typical TU) - a function with fewer candidates than
  that cannot be picked out this way.
* `--find LOCALNAME` prints every *named* candidate with its invocation index, so the
  function can be identified by one of its locals instead of by size. This is the reliable
  mode; `--probe` is the quick one.
* `--invocation N` dumps that invocation's candidates as `score, symbol id, name`, in the
  order the compiler scored them. `(temp)` is a compiler temporary with no source name.

Candidates recur with different scores because the colourer iterates, re-scoring between
rounds; the first block is the initial scoring.

Reading the output: a value with a high score is served early and gets its pick of the
registers, a negative one is likely to be spilled or to land in whatever is left. Comparing
two source variants of the same function shows whether a change moved the value you care
about up or down the list, which is otherwise only visible as an unexplained register
permutation in the reccmp diff.
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
GLOBAL_REG_ALLOC = '0x10c07350'      # @dop2_GlobalRegAlloc@4
INSERT_IN_LIST = '0x10b11970'        # @InsertInList@8, the candidate priority insert
BS = chr(92)

args = [a for a in sys.argv[1:] if not a.startswith('--')]
probe = '--probe' in sys.argv
find = '--find' in sys.argv
inv = None
for a in sys.argv[1:]:
    if a.startswith('--invocation'):
        inv = a.split('=', 1)[1] if '=' in a else None
if inv is None and '--invocation' in sys.argv:
    i = sys.argv.index('--invocation')
    if i + 1 < len(sys.argv):
        inv = sys.argv[i + 1]
if not args or (not probe and not find and not inv):
    sys.exit(__doc__)
src = os.path.abspath(args[0])
out = (common.ROOT / common.TMP / 'regscores').resolve()
out.mkdir(parents=True, exist_ok=True)


def compile_command():
    cc = json.loads(common.read_text(common.BUILD_DIR / 'compile_commands.json'))
    ours = [e for e in cc if 'OpenSHC.dll.dir' in e['command']
            and '/src/OpenSHC/' in e['file'].replace('\\', '/')]
    if not ours:
        sys.exit('configure the build first: no OpenSHC.dll entry in compile_commands.json')
    o = str(out).replace('\\', '/')
    cmd = re.sub(r'/Fo\S+', lambda _m: '/Fo%s/r.obj' % o, ours[0]['command'])
    cmd = re.sub(r'-c \S+$', lambda _m: '-c ' + src, cmd)
    return cmd, ours[0]['directory']


def run(script_lines, tag):
    path = out / (tag + '.cdb')
    common.write_text(path, '\r\n'.join(script_lines) + '\r\n')
    cmd, cwd = compile_command()
    env = common.build_env()
    env['PATH'] = str(common.ROOT / 'MSVC1400-SP1' / 'Common7' / 'IDE') + os.pathsep + env['PATH']
    full = '"%s" -cf "%s" %s' % (CDB, path, cmd)
    r = subprocess.run(full, cwd=cwd, env=env, capture_output=True, text=True, timeout=3600)
    common.write_text(out / (tag + '.log'), r.stdout)
    return r.stdout


if find:
    # every named candidate with its invocation index: identification by name, which works
    # for functions smaller than the resolver-template flood that --probe ranks by size
    q = BS + '"'
    cand = ('.if (poi(poi(@eax)) != 0) { .printf ' + q + 'N %d %d ' + q +
            ', @$t0, poi(@eax+0xc); da poi(poi(poi(@eax))+4)+1 L28 }; gc')
    lines = ['sxe ld:c2', 'g', 'r $t0=0',
             'bp1 ' + INSERT_IN_LIST + ' "' + cand + '"',
             'bp0 ' + GLOBAL_REG_ALLOC + ' "r $t0=@$t0+1; gc"',
             'g', 'q', '']
    txt = run(lines, 'find')
    rows = {}
    for m in re.finditer(r'N (\d+) (-?\d+) [0-9a-f]{8}\s+"([^"]*)"', txt):
        rows.setdefault(int(m.group(1)), []).append((int(m.group(2)), m.group(3)))
    want = [a for a in sys.argv[1:] if not a.startswith('--') and not a.endswith('.cpp')]
    print('invocations holding a named candidate: %d' % len(rows))
    for i in sorted(rows):
        names = [n for _s, n in rows[i]]
        if not want or any(w in names for w in want):
            print('  #%-5d %s' % (i, ', '.join('%s(%+d)' % (n, s) for s, n in rows[i])))
    sys.exit(0)

if probe:
    # count candidate inserts per invocation, print only the busy ones
    lines = ['sxe ld:c2', 'g', 'r $t0=0', 'r $t1=0',
             'bp0 ' + GLOBAL_REG_ALLOC + ' ".if (@$t1 > 0n15) { .printf ' + BS + '"RA %d %d' +
             BS + BS + 'n' + BS + '", @$t0, @$t1 }; r $t1=0; r $t0=@$t0+1; gc"',
             'bp1 ' + INSERT_IN_LIST + ' "r $t1=@$t1+1; gc"',
             'g', 'q', '']
    txt = run(lines, 'probe')
    rows = [(int(b), int(a)) for a, b in re.findall(r'RA (\d+) (\d+)', txt)]
    if not rows:
        sys.exit('no invocation inserted more than 15 candidates - check the build and the file')
    print('%-6s %s' % ('cands', 'invocation'))
    for n, i in sorted(rows, reverse=True)[:15]:
        print('%-6d #%d' % (n, i))
    print('\nnow: reg_scores.py %s --invocation <N>' % args[0])
    sys.exit(0)

q = BS + '"'
cand = ('.printf ' + q + 'CAND %4d %02x ' + q + ', poi(@eax+0xc), poi(@eax+0x44); '
        '.if (poi(poi(@eax)) != 0) { da poi(poi(poi(@eax))+4)+1 L28 } '
        '.else { .printf ' + q + '(temp)' + BS + BS + 'n' + q + ' }; gc')
lines = ['sxe ld:c2', 'g', 'r $t0=0',
         'bp1 ' + INSERT_IN_LIST + ' "' + cand + '"',
         'bd 1',
         'bp0 ' + GLOBAL_REG_ALLOC + ' "r $t0=@$t0+1; .if (@$t0==0n' + str(int(inv)) +
         ') { be 1 }; .if (@$t0==0n' + str(int(inv) + 1) + ') { bd 1 }; gc"',
         'g', 'q', '']
txt = run(lines, 'inv' + str(int(inv)))
rows = []
for m in re.finditer(r'CAND\s+(-?\d+)\s+([0-9a-f]+)\s*(?:\(temp\)|[0-9a-f]{8}\s+"([^"]*)")', txt):
    rows.append((int(m.group(1)), m.group(2), m.group(3) or '(temp)'))
if not rows:
    sys.exit('no candidates seen for invocation %s - run --probe to pick one' % inv)
print('%-6s %-5s %s' % ('score', 'id', 'name'))
for score, sid, name in rows:
    print('%-6d %-5s %s' % (score, sid, name))
print('\n%d candidates; higher score is served first and gets its pick of the registers.' % len(rows))

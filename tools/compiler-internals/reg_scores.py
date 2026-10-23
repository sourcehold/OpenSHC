"""Print the register-candidate scores MSVC computes for one of our functions.

usage: reg_scores.py FILE.cpp --probe
       reg_scores.py FILE.cpp --find [LOCALNAME ...]
       reg_scores.py FILE.cpp --advise LOCALNAME
       reg_scores.py FILE.cpp --invocation N

`OrderGlobregs` orders the candidate values and `Color` walks that order, calling
`ChoosePhysReg` to serve each from the still-available registers. The ordering key is the
candidate's **benefit** at `+0x40`, which is a weighted use count - `amount` in
`sellExcessGoods`, assigned in eight branches and read by the call, scores 70 where
`playerID` scores 4. This script reads those numbers out of the running compiler with the
candidates resolved back to source variable names.

The benefit is a property of what the code *does*, not of how it is written: it counts uses
weighted by block frequency. No reordering, renaming or redeclaring moves it, which is why
syntactic hill-climbing does not shift a register assignment. What can move it is changing
how many times, and at what loop depth, a value is actually used.

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
* `--advise LOCALNAME` prints the score table per candidate and names the patterns in it.

On what `--advise` is worth: its suggestions were tested on `aiRecruitUnits` (50.0%), whose
scores show the strongest structural signal of any function tried - a loop counter `i` at
-279 and a flag `recruitDiggingUnit` at -335 against a +188 top. Both suggested fixes made
the match *worse*: eliminating the counter by counting `recruitCount` down gave 48.7%, and
declaring the flag `bool` as Ghidra renders it gave 49.5%. Removing a disfavoured candidate
changes the whole scoring landscape - fewer candidates means different spill rounds - so
"delete the worst one" is not a monotone improvement.

Treat the output as triage, not prescription. The reliably useful verdict is the negative
one: when several candidates share a score, the order falls to the symbol-id tiebreak, no
source change can state a preference, and the right move is to stop working on that
function. That saves effort rather than adding points.

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
advise = '--advise' in sys.argv
inv = None
for a in sys.argv[1:]:
    if a.startswith('--invocation'):
        inv = a.split('=', 1)[1] if '=' in a else None
if inv is None and '--invocation' in sys.argv:
    i = sys.argv.index('--invocation')
    if i + 1 < len(sys.argv):
        inv = sys.argv[i + 1]
if not args or (not probe and not find and not advise and not inv):
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


def advise_on(rows):
    """Turn one invocation's (score, name) list into suggestions worth measuring."""
    first, allscores = {}, {}
    for sc, nm in rows:
        allscores.setdefault(nm, []).append(sc)
        first.setdefault(nm, sc)
    named = {n: v for n, v in first.items() if n != '(temp)'}
    print('')
    print('%-28s %-8s %s' % ('candidate', 'first', 'all rounds'))
    for n in sorted(named, key=lambda k: -named[k]):
        print('%-28s %-8d %s' % (n, named[n], ' '.join('%+d' % x for x in allscores[n])))
    print('')
    out = []

    # near-ties: with equal scores the order falls to the symbol-id tiebreak
    buckets = {}
    for n, v in named.items():
        buckets.setdefault(v, []).append(n)
    ties = {v: ns for v, ns in buckets.items() if len(ns) > 1}
    tied = sum(len(ns) for ns in ties.values())
    if tied >= 3:
        detail = '; '.join('%+d: %s' % (v, ', '.join(ns)) for v, ns in sorted(ties.items(), reverse=True))
        out.append(['NEAR-TIES: %d candidates share a score (%s).' % (tied, detail),
                    'With equal scores the order falls to the symbol-id tiebreak, so no source change',
                    'states a preference here. Expect small edits to flip the result arbitrarily, and',
                    'do not spend hill-climbing effort on this function.'])

    # a strongly disfavoured candidate is a local the original may not carry at all
    spread = (max(named.values()) - min(named.values())) if named else 0
    for n, v in sorted(named.items(), key=lambda kv: kv[1])[:3]:
        if v < -100 and spread > 150:
            msg = ['DISFAVOURED: %s scores %+d against a spread of %d.' % (n, v, spread),
                   'A candidate this far down is one the original may not carry separately.',
                   'Try removing it, or letting a value that already exists carry it.']
            if n in ('i', 'j', 'k', 'index', 'idx', 'counter'):
                msg.append('It is a loop counter: the original often reuses something it already has -')
                msg.append('a dead parameter, or counting an existing local down - costing no candidate.')
            out.append(msg)

    # sign flips mean the colourer's later rounds decide, not one ordering
    flips = sorted(n for n, v in allscores.items() if n != '(temp)' and min(v) < 0 < max(v))
    if len(flips) >= 3:
        out.append(['ITERATION-DEPENDENT: %s start negative and only turn positive later.' % ', '.join(flips[:6]),
                    'The layout is settled by the spill rounds rather than by one ordering, so a single',
                    'declaration permutation will not move it.'])

    if not out:
        out.append(['No pattern stands out: the scores are spread and untied, so the ordering does follow',
                    'from how the values are used. Changing how often or where a value is read should move it.'])
    for i, msg in enumerate(out, 1):
        print('%d. %s' % (i, msg[0]))
        for extra in msg[1:]:
            print('   ' + extra)
    print('')
    print('Every suggestion above is a hypothesis about codegen, not a verified fix.')
    print('Measure each one with reccmp_report.py --run before keeping it.')


if find or advise:
    # every named candidate with its invocation index: identification by name, which works
    # for functions smaller than the resolver-template flood that --probe ranks by size
    q = BS + '"'
    cand = ('.if (poi(poi(@eax)) != 0) { .printf ' + q + 'N %d %d %d ' + q +
            ', @$t0, poi(@eax+0x40), poi(@eax+0xc); da poi(poi(poi(@eax))+4)+1 L28 }; gc')
    lines = ['sxe ld:c2', 'g', 'r $t0=0',
             'bp1 ' + INSERT_IN_LIST + ' "' + cand + '"',
             'bp0 ' + GLOBAL_REG_ALLOC + ' "r $t0=@$t0+1; gc"',
             'g', 'q', '']
    txt = run(lines, 'find')
    rows = {}
    for m in re.finditer(r'N (\d+) (-?\d+) (-?\d+) [0-9a-f]{8}\s+"([^"]*)"', txt):
        rows.setdefault(int(m.group(1)), []).append((int(m.group(2)), m.group(4)))
    want = [a for a in sys.argv[1:] if not a.startswith('--') and not a.endswith('.cpp')]
    hits = [i for i in sorted(rows)
            if not want or any(w in [n for _s, n in rows[i]] for w in want)]
    if advise:
        if not hits:
            sys.exit('no invocation holds a candidate named %s - try another local' % ', '.join(want))
        if len(hits) > 1:
            print('note: %d invocations match; advising on the largest' % len(hits))
        pick = max(hits, key=lambda i: len(rows[i]))
        print('### invocation #%d, %d candidates' % (pick, len(rows[pick])))
        advise_on(rows[pick])
        sys.exit(0)
    print('invocations holding a named candidate: %d' % len(rows))
    for i in hits:
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
cand = ('.printf ' + q + 'CAND %4d %02x ' + q + ', poi(@eax+0x40), poi(@eax+0x44); '
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

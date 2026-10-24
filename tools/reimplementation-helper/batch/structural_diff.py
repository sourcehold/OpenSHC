"""Score a function by *structure* rather than by match percentage.

usage: structural_diff.py [NAME-SUBSTRING]        one function, full report
       structural_diff.py --all                   every function in the build list, ranked
       structural_diff.py NAME --score            one number, for hill-climbing

The reccmp percentage is dominated by register and stack-slot naming, which the source cannot
state directly. On `aiRecruitUnits` the 50% gap decomposes as roughly 7% instruction kind and
order, 4% operand shape, and 39% pure register naming. Optimising the percentage therefore
steers by the one term that is not reachable, and it can select *against* structural
correctness: `recruitCount++` gets the original's `neg`/`sbb`/`jmp` counts right and scores
47.3%, while `recruitCount = interval != 0 ? 2 : 3` gets those counts wrong and scores 50.0%.

Register allocation is deterministic given the compiler's IR, so the way to reach 100% is to
make the instruction stream identical in kind and order and let the allocation follow - which
is what happened to the sixteen `setAICParameters_NN` functions, where fixing statement order
fixed the register assignment by itself. This script scores the part you can act on.

Three tiers are reported, each ignoring more than the last:

* `kind`  - bare mnemonic sequence, every operand stripped. Differences here are real: a
            different instruction, a missing one, a different order. This is the tier to drive
            to 1.000 first.
* `shape` - operands kept but registers anonymised to `r` and immediates to `k`. Differences
            here are operand form: a memory access against an immediate, a different
            addressing mode, a constant where the original has a register.
* `raw`   - what reccmp reports, for reference.

`delta` sums the per-mnemonic count mismatches, which is the most directly actionable figure:
it says "we emit two `xor` the original does not" rather than giving a ratio. Chase it to zero.

Needs a current `reccmp_report.py --run`. Reads the same `diff.json` as the other tools, so it
costs nothing to run.
"""

import collections
import difflib
import re
import sys

import common

SCORE_ONLY = '--score' in sys.argv
ALL = '--all' in sys.argv
want = next((a for a in sys.argv[1:] if not a.startswith('--')), None)
if not ALL and want is None:
    sys.exit(__doc__)

REG = re.compile(r'\b(e?(?:ax|bx|cx|dx|si|di|bp|sp)|[a-d][lh]|al|ah)\b')
IMM = re.compile(r'\b(?:0x[0-9a-f]+|\d+)\b')


def mnemonic(line):
    return line.split()[0] if line.split() else ''


def shape(line):
    """Operand form with register names and constants anonymised."""
    out = REG.sub('r', line)
    out = IMM.sub('k', out)
    return out


def ratio(a, b):
    return difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()


def measure(entry):
    orig, ours = common._asm_lines(entry)
    orig = [l.strip() for l in orig if l.strip()]
    ours = [l.strip() for l in ours if l.strip()]
    mo, mu = [mnemonic(l) for l in orig], [mnemonic(l) for l in ours]
    so, su = [shape(l) for l in orig], [shape(l) for l in ours]
    co, cu = collections.Counter(mo), collections.Counter(mu)
    kinds = sorted(set(co) | set(cu))
    deltas = [(k, co.get(k, 0), cu.get(k, 0)) for k in kinds if co.get(k, 0) != cu.get(k, 0)]
    return {
        'name': entry['name'],
        'raw': float(entry['matching']),
        'kind': ratio(mo, mu),
        'shape': ratio(so, su),
        'n_orig': len(orig),
        'n_ours': len(ours),
        'delta': sum(abs(a - b) for _k, a, b in deltas),
        'deltas': sorted(deltas, key=lambda t: -abs(t[1] - t[2])),
    }


def report(m):
    print('### %s' % m['name'])
    print('  instructions   original %d   ours %d   (%+d)'
          % (m['n_orig'], m['n_ours'], m['n_ours'] - m['n_orig']))
    print('  kind  %.3f   <- drive this to 1.000 first; every difference here is real'
          % m['kind'])
    print('  shape %.3f   <- operand form, once registers and constants are anonymised'
          % m['shape'])
    print('  raw   %.3f   <- reccmp, mostly register and slot naming' % m['raw'])
    print('  delta %d instruction(s) of mismatched kind' % m['delta'])
    if m['deltas']:
        print('')
        print('  %-8s %-8s %-8s' % ('mnemonic', 'original', 'ours'))
        for k, a, b in m['deltas']:
            print('  %-8s %-8d %-8d  %+d' % (k, a, b, b - a))
        print('')
        print('  Each row is a hypothesis: an extra `xor` is a value materialised differently,')
        print('  a missing `lea` is an address the original folds, `jmp` with `cmp` one apart is')
        print('  a branch shaped differently. Fix these and let the allocation follow.')
    elif m['kind'] < 0.99:
        print('')
        print('  No mnemonic mismatch, but the sequences differ: the two sides emit the same')
        print('  instructions in a different ORDER. That is statement order, and it is reachable -')
        print('  it is what took the sixteen setAICParameters_NN functions to 100%. Use the')
        print('  original stream (orig_asm.py NAME) as the skeleton and reorder the source to it.')
    else:
        print('')
        print('  Same instructions, same order. What is left is operand form and register naming,')
        print('  so there is no structural work to do here - see tools/compiler-internals.')


def entries():
    byaddr = common.load_diff()
    for _f, e, _a in common.entries(byaddr):
        if e is None or not e.get('diff'):
            continue
        yield e


if ALL:
    rows = [measure(e) for e in entries()]
    rows = [r for r in rows if r['raw'] < 0.9999]
    if not rows:
        sys.exit('every function in the build list matches; nothing to rank')
    rows.sort(key=lambda r: (-r['delta'], r['kind']))
    print('%-50s %6s %6s %6s %5s  %s' % ('function', 'kind', 'shape', 'raw', 'delta', 'verdict'))
    for r in rows:
        if r['delta'] > 0:
            verdict = 'mix'
        elif r['kind'] < 0.99:
            verdict = 'order'
        else:
            verdict = 'allocation'
        print('%-50s %6.3f %6.3f %6.3f %5d  %s'
              % (r['name'].split('::')[-1], r['kind'], r['shape'], r['raw'], r['delta'], verdict))
    print('')
    print('Three categories, in descending order of how reachable they are from the source:')
    print('  delta > 0                  wrong instruction mix. Each mismatched mnemonic is a')
    print('                             concrete defect; this is where source work pays.')
    print('  delta 0, kind < 0.99       right mix, wrong order - statement order, reachable.')
    print('  delta 0, kind ~ 1.000      same instructions in the same order. The gap is operand')
    print('                             form and register naming; leave these alone.')
    sys.exit(0)

hits = [e for e in entries() if want in e['name']]
if not hits:
    sys.exit('no function matching %r in the last reccmp run' % want)
for e in hits:
    m = measure(e)
    if SCORE_ONLY:
        print('%.4f %d' % (m['kind'], m['delta']))
    else:
        report(m)

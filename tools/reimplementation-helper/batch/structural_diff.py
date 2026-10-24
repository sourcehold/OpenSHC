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

Both instruction streams are complete, and come from the code itself via `asm_streams.py` - the
original disassembled from `_original/`, ours from a `/FA` compile. They deliberately do NOT
come from `reccmp/dll/diff.json`, which holds only the diff view and therefore keeps *less* of a
function the better it matches: `aiCreateSiegeUnits` at 99.7% leaves 22 lines per side behind,
against a real body of 322 instructions. An earlier version of this script read those lines, and
its figures for well-matching functions were meaningless. Only `raw` still comes from reccmp.

Each function is compiled on demand, so `--all` takes about a second per file and needs a
configured build directory - but no build and no reccmp run, except for the `raw` column.
"""

import collections
import difflib
import os
import re
import sys

import asm_streams
import common

SCORE_ONLY = '--score' in sys.argv
ALL = '--all' in sys.argv
want = next((a for a in sys.argv[1:] if not a.startswith('--')), None)
if not ALL and want is None:
    sys.exit(__doc__)

REG = re.compile(r'\b(e?(?:ax|bx|cx|dx|si|di|bp|sp)|[a-d][lh])\b')
IMM = re.compile(r'\b(?:0x[0-9a-f]+|\d+)\b')
NAMED = re.compile(r'\b(e(?:ax|bx|cx|dx|si|di|bp))\b')


def shape(line):
    """Operand form with register names and constants anonymised."""
    return IMM.sub('k', REG.sub('r', line))


def skeleton(line):
    """The instruction with only its register NAMES anonymised."""
    return NAMED.sub('r', line)


def register_divergence(orig, ours):
    """Where each side first diverges, and how the register names map.

    A function can be structurally identical and still score badly purely because the
    registers are named differently, and the two cases need opposite responses - so it
    matters which one you are looking at. The discriminator is WHERE each kind of difference
    starts. Register allocation is deterministic given the IR, so when the first register
    difference sits at or after the first structural difference, the registers are an *effect*
    of that structural defect and will follow once it is fixed; attacking them directly is
    wasted work. There is also no cost-side lever to attack them with: in `ChoosePhysReg` the
    per-register cost array came out all zeros for every pick in `renderDebugDataAiInfo`, so
    the choice was simply the first free register in class order.

    That function is the worked case: 293 of its 305 instructions align once register names
    are stripped, the first 149 have identical registers, and the rotation starts inside the
    one block whose instruction stream still differs.
    """
    so = [skeleton(l) for l in orig]
    su = [skeleton(l) for l in ours]
    # the first STRUCTURAL difference is measured on mnemonics alone. Measuring it on whole
    # operands instead puts it at instruction 1 of almost every function, because our side
    # names `___security_cookie` where the original has a bare address - a symbolisation
    # difference, not a structural one, and it would make the comparison below meaningless.
    mo = [l.split()[0] for l in orig if l.split()]
    mu = [l.split()[0] for l in ours if l.split()]
    ops = difflib.SequenceMatcher(None, mo, mu, autojunk=False).get_opcodes()
    first_struct = next((i1 for tag, i1, _i2, _j1, _j2 in ops if tag != 'equal'), None)
    sm = difflib.SequenceMatcher(None, so, su, autojunk=False)
    first_reg = None
    aligned = 0
    subs = collections.Counter()
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != 'equal':
            continue
        for k in range(i2 - i1):
            aligned += 1
            ra = NAMED.findall(orig[i1 + k])
            rb = NAMED.findall(ours[j1 + k])
            if ra != rb:
                if first_reg is None:
                    first_reg = i1 + k
                for a, b in zip(ra, rb):
                    if a != b:
                        subs[(a, b)] += 1
    return {'skel': sm.ratio(), 'aligned': aligned, 'first_struct': first_struct,
            'first_reg': first_reg, 'subs': subs}


def ratio(a, b):
    return difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()


def measure(path, name, raw):
    orig, ours = asm_streams.streams(path)
    if ours is None:
        return None
    mo, mu = asm_streams.mnemonics(orig), asm_streams.mnemonics(ours)
    co, cu = collections.Counter(mo), collections.Counter(mu)
    deltas = [(k, co.get(k, 0), cu.get(k, 0)) for k in sorted(set(co) | set(cu))
              if co.get(k, 0) != cu.get(k, 0)]
    return {
        'name': name,
        'raw': raw,
        'div': register_divergence(orig, ours),
        'kind': ratio(mo, mu),
        'shape': ratio([shape(l) for l in orig], [shape(l) for l in ours]),
        'n_orig': len(mo),
        'n_ours': len(mu),
        'delta': sum(abs(a - b) for _k, a, b in deltas),
        'deltas': sorted(deltas, key=lambda t: -abs(t[1] - t[2])),
    }


def report_registers(div):
    """Say whether the register naming is a cause or an effect."""
    if not div['subs']:
        return
    fs, fr = div['first_struct'], div['first_reg']
    print('')
    total = sum(div['subs'].values())
    print('  registers: %d operand(s) differ only in which register was used.' % total)
    print('  %-14s %s' % ('substitution', 'count'))
    for (a, b), c in div['subs'].most_common(6):
        print('  %-4s -> %-6s %5d' % (a, b, c))
    # A permutation that closes into a cycle means the allocation is structurally right and
    # the scratch registers were simply handed out in a different order. Take each source
    # register's most common target rather than any target, and report what share of the
    # substitutions that permutation actually covers - the minority ones are real and
    # claiming a clean cycle over them would overstate the result.
    best = {}
    for (a, b), c in div['subs'].most_common():
        if a not in best:
            best[a] = (b, c)
    mapping = dict((a, b) for a, (b, _c) in best.items())
    covered = sum(c for _a, (_b, c) in best.items())
    closed = (len(set(mapping.values())) == len(mapping)
              and all(b in mapping for b in mapping.values())
              and len(mapping) > 2)
    if closed:
        cycle = []
        a = sorted(mapping)[0]
        for _ in range(len(mapping)):
            cycle.append(a)
            a = mapping[a]
        print('')
        print('  The dominant substitution is a closed cycle %s, covering %d of %d (%.0f%%).'
              % (' -> '.join(cycle + [cycle[0]]), covered, total, 100.0 * covered / total))
        print('  A closed cycle means the allocation is structurally right and the scratch')
        print('  registers were merely handed out in a different order.')
    if fs is not None and fr is not None and fr >= fs:
        print('')
        print('  The first STRUCTURAL difference is at original instruction %d and the first' % fs)
        print('  REGISTER difference at %d, so the registers diverge at or after the structure'
              % fr)
        print('  does. Allocation is deterministic given the IR, so these register names are')
        print('  an effect of that structural defect - fix it and they follow. Where this was')
        print('  measured (renderDebugDataAiInfo) there was also no cost-side lever to pull:')
        print('  ChoosePhysReg picked on an all-zero cost array, so the first free register in')
        print('  class order won. Check it per function with reg_scores.py --whyreg.')
    elif fr is not None and (fs is None or fr < fs):
        print('')
        print('  The registers diverge at instruction %d, BEFORE any structural difference' % fr)
        print('  (%s), so this is not downstream of a mix defect. The levers are the order'
              % ('none at all' if fs is None else 'at %d' % fs))
        print('  values are created in and what is live across each point - statement order -')
        print('  not how anything is spelled or typed. See tools/compiler-internals.')


def report(m):
    print('### %s' % m['name'])
    print('  instructions   original %d   ours %d   (%+d)'
          % (m['n_orig'], m['n_ours'], m['n_ours'] - m['n_orig']))
    print('  kind  %.3f   <- drive this to 1.000 first; every difference here is real'
          % m['kind'])
    print('  shape %.3f   <- operand form, once registers and constants are anonymised'
          % m['shape'])
    print('  skel  %.3f   <- the same instructions with only REGISTER NAMES anonymised'
          % m['div']['skel'])
    if m['raw'] is not None:
        print('  raw   %.3f   <- reccmp, mostly register and slot naming' % m['raw'])
    print('  delta %d instruction(s) of mismatched kind' % m['delta'])
    report_registers(m['div'])
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
        print('  instructions in a different ORDER. That is statement order, and it is reachable')
        print('  - it is what took the sixteen setAICParameters_NN functions to 100%. Use the')
        print('  original stream (orig_body.py FILE) as the skeleton and reorder the source.')
    else:
        print('')
        print('  Same instructions, same order. What is left is operand form and register naming,')
        print('  so there is no structural work to do here - see tools/compiler-internals.')


def targets():
    """[(path, name, raw)] for the build list; `raw` is None when reccmp has no entry."""
    byaddr = common.load_diff()
    for f, e, _a in common.entries(byaddr):
        # the build list is git-ignored, so it routinely names files that are not on the
        # current branch; both streams need the source, so such an entry has to be skipped
        if not os.path.exists(f):
            continue
        name = e['name'] if e else common.repo_relative(f)
        yield f, name, (float(e['matching']) if e else None)


if ALL:
    rows = []
    for f, name, raw in targets():
        if raw is not None and raw >= 0.9999:
            continue
        try:
            m = measure(f, name, raw)
        except Exception as exc:
            print('# %-44s skipped: %s: %s' % (name, type(exc).__name__, exc))
            continue
        if m:
            rows.append(m)
    if not rows:
        sys.exit('every function in the build list matches; nothing to rank')
    rows.sort(key=lambda r: (-r['delta'], r['kind']))
    print('%-50s %6s %6s %6s %5s  %s' % ('function', 'kind', 'shape', 'raw', 'delta', 'verdict'))
    for r in rows:
        verdict = 'mix' if r['delta'] > 0 else ('order' if r['kind'] < 0.99 else 'allocation')
        print('%-50s %6.3f %6.3f %6s %5d  %s'
              % (r['name'].split('::')[-1], r['kind'], r['shape'],
                 '-' if r['raw'] is None else '%.3f' % r['raw'], r['delta'], verdict))
    print('')
    print('Three categories, in descending order of how reachable they are from the source:')
    print('  delta > 0                  wrong instruction mix. Each mismatched mnemonic is a')
    print('                             concrete defect; this is where source work pays.')
    print('  delta 0, kind < 0.99       right mix, wrong order - statement order, reachable.')
    print('  delta 0, kind ~ 1.000      same instructions in the same order. The gap is operand')
    print('                             form and register naming; leave these alone.')
    sys.exit(0)

hits = [(f, n, r) for f, n, r in targets()
        if want.lower() in n.lower() or want.lower() in f.lower()]
if not hits:
    sys.exit('no function matching %r in the build list' % want)
for f, n, r in hits:
    m = measure(f, n, r)
    if m is None:
        continue
    if SCORE_ONLY:
        print('%.4f %d' % (m['kind'], m['delta']))
    else:
        report(m)

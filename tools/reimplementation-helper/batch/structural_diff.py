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

# parsed in main(), not at import: the other tools import this module for `measure()` and
# `duplication()`, and a module-level sys.exit turns that into an abrupt exit with a usage dump
SCORE_ONLY = False
ALL = False

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
        'dup': duplication(orig, ours),
        'flips': polarity(orig, ours),
        'kind': ratio(mo, mu),
        'shape': ratio([shape(l) for l in orig], [shape(l) for l in ours]),
        'n_orig': len(mo),
        'n_ours': len(mu),
        'delta': sum(abs(a - b) for _k, a, b in deltas),
        'deltas': sorted(deltas, key=lambda t: -abs(t[1] - t[2])),
    }


NEGATION = {'je': 'jne', 'jne': 'je', 'jl': 'jge', 'jge': 'jl', 'jg': 'jle', 'jle': 'jg',
            'jb': 'jae', 'jae': 'jb', 'ja': 'jbe', 'jbe': 'ja', 'js': 'jns', 'jns': 'js',
            'jp': 'jnp', 'jnp': 'jp'}


def polarity(orig, ours):
    """Branches where one side jumps on a condition and the other on its negation.

    `diff_jcc.py` covers strictness steps (`jl` against `jle`) and swapped compare operands,
    but not a plain polarity flip, which is a different source defect: the `if`/`else` arms are
    the other way round, so the original's fallthrough is our jump target. Worth 56.8% -> 60.3%
    on `aiGiveRaidInstructions`, whose final navigation test read `== FALSE` where the original
    had `!= FALSE`.

    Only pairs inside a differing region are considered, positionally - a flip shows up there
    because the inverted branch makes the surrounding block fail to align.
    """
    so = [skeleton(l) for l in orig]
    su = [skeleton(l) for l in ours]
    out = []
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, so, su,
                                                       autojunk=False).get_opcodes():
        if tag != 'replace':
            continue
        ob = [(i1 + k, orig[i1 + k].split()[0]) for k in range(i2 - i1)
              if orig[i1 + k].split() and orig[i1 + k].split()[0] in NEGATION]
        ub = [(j1 + k, ours[j1 + k].split()[0]) for k in range(j2 - j1)
              if ours[j1 + k].split() and ours[j1 + k].split()[0] in NEGATION]
        for (oi, om), (_uj, um) in zip(ob, ub):
            if NEGATION[om] == um:
                out.append((oi, om, um, ' / '.join(orig[max(0, oi - 2):oi])))
    return out


def report_polarity(flips):
    """Name an inverted branch and how to fix it."""
    if not flips:
        return
    print('')
    print('  POLARITY: %d branch(es) jump on the opposite condition:' % len(flips))
    for oi, om, um, ctx in flips[:4]:
        print('      original instruction %-4d  original %-4s ours %-4s' % (oi, om, um))
        if ctx:
            print('          preceded by: %s' % ctx[:70])
    print('')
    print('  The original falls through where we jump, so its `if`/`else` arms are the other')
    print('  way round. Swap them and invert the test - semantically identical, and it is what')
    print('  took aiGiveRaidInstructions from 56.8% to 60.3%. Note diff_jcc.py does NOT report')
    print('  this: it covers strictness steps and operand order, not a plain polarity flip.')


def _count_run(lines, run):
    """How many non-overlapping times `run` occurs in `lines`."""
    n, i, total = len(run), 0, 0
    while i + n <= len(lines):
        if lines[i:i + n] == run:
            total += 1
            i += n
        else:
            i += 1
    return total


def duplication(orig, ours):
    """Computations one side repeats and the other shares.

    This is the signal that is easy to misread. When MSVC hoists an expression out of both
    arms of an `if`/`else` and the original did not, the mix delta shows up as one missing
    copy of each mnemonic in the run - on `renderDebugDataAiInfo` it read `add -1, mov -1,
    push -1`, which looks like three unrelated missing instructions and is really one missing
    duplicate of `mov reg, [reg + G]; add reg, 1; push reg`.

    Comparing the number of occurrences, with registers anonymised so the two copies match
    despite being allocated differently, names it directly. The fix direction follows from
    which side repeats: MSVC hoists the *maximal* common expression, so if the original
    repeats a run that we share, writing the whole expression out in both arms will not
    reproduce it - the source has to share exactly the prefix the original shares, typically
    an index in a local, and write the rest out.
    """
    so = [skeleton(l) for l in orig]
    su = [skeleton(l) for l in ours]
    sm = difflib.SequenceMatcher(None, so, su, autojunk=False)
    found = []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal':
            continue
        # whichever side has the surplus instructions in this region is the side that might
        # be repeating something; a `replace` can hold a whole extra copy too
        if tag == 'delete' or (tag == 'replace' and (i2 - i1) >= (j2 - j1)):
            extra, side, mine, other = so[i1:i2], 'original', so, su
        else:
            extra, side, mine, other = su[j1:j2], 'ours', su, so
        # Search the region's sub-runs, longest first: the repeated computation is often only
        # part of a larger differing region. Require the run to occur at least TWICE on its
        # own side - otherwise a single instruction that merely MOVED looks like a
        # duplication, which is what a first version of this reported (`cmp`/`jne` at 1 vs 0).
        best = None
        for length in range(len(extra), 1, -1):
            for start in range(0, len(extra) - length + 1):
                run = extra[start:start + length]
                c_mine = _count_run(mine, run)
                if c_mine < 2:
                    continue
                c_other = _count_run(other, run)
                if c_mine > c_other:
                    best = (side, run, c_mine, c_other)
                    break
            if best:
                break
        if best:
            found.append(best)
    # the longest run is the most informative, and duplicate reports of the same run add
    # nothing
    seen, out = set(), []
    for side, run, mine_c, other_c in sorted(found, key=lambda f: -len(f[1])):
        key = (side, tuple(run))
        if key in seen:
            continue
        seen.add(key)
        out.append((side, run, mine_c, other_c))
    return out


def report_duplication(found):
    """Name a hoisted-or-not-hoisted duplicate and which way to fix it."""
    for side, run, mine, theirs in found[:3]:
        print('')
        if side == 'original':
            print('  DUPLICATION: the original computes this run %d time(s), we compute it %d:'
                  % (mine, theirs))
        else:
            print('  DUPLICATION: we compute this run %d time(s), the original computes it %d:'
                  % (mine, theirs))
        for line in run[:8]:
            print('      %s' % line)
        if len(run) > 8:
            print('      ... %d more' % (len(run) - 8))
        print('')
        if side == 'original':
            print('  So MSVC hoisted out of a branch what the original left duplicated. It hoists')
            print('  the MAXIMAL common expression, so writing the whole expression out in both')
            print('  arms will NOT reproduce this - that only makes the whole chain common. Share')
            print('  in the source exactly the prefix the original shares (an index or a base in a')
            print('  local) and write the rest out in each arm. Sharing more than it did costs an')
            print('  instruction too: a pointer to the element pays an `add` where the original')
            print('  keeps index*size and re-folds the base into each load.')
        else:
            print('  So we recompute in each arm what the original computes once. Introduce a')
            print('  local for it, placed where the original shares it.')
        print('  Worked example: tools/compiler-internals/msvc-backend.md, the AIV block of')
        print('  renderDebugDataAiInfo - this exact signal was 67.5% -> 83.6%.')


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
        # decompose into disjoint cycles and walk each until it returns to its start. Running
        # one walk for len(mapping) steps instead printed nonsense whenever the permutation
        # had more than one cycle - `eax -> ecx -> edx -> eax -> ecx -> eax` for what is
        # really ebp <-> ebx alongside eax -> ecx -> edx -> eax.
        cycles, seen_r = [], set()
        for start in sorted(mapping):
            if start in seen_r:
                continue
            cycle, a = [], start
            while a not in seen_r:
                seen_r.add(a)
                cycle.append(a)
                a = mapping[a]
            cycles.append(cycle)
        print('')
        shown = ', '.join(' -> '.join(c + [c[0]]) if len(c) > 1 else '%s (unchanged)' % c[0]
                          for c in cycles)
        print('  The dominant substitution is a permutation in %d closed cycle(s), covering'
              % len(cycles))
        print('  %d of %d (%.0f%%): %s' % (covered, total, 100.0 * covered / total, shown))
        print('  Closed cycles mean the allocation is structurally right and the registers')
        print('  were merely handed out in a different order.')
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
    report_polarity(m['flips'])
    report_duplication(m['dup'])
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


def main():
    global SCORE_ONLY, ALL
    SCORE_ONLY = '--score' in sys.argv
    ALL = '--all' in sys.argv
    want = next((a for a in sys.argv[1:] if not a.startswith('--')), None)
    if not ALL and want is None:
        sys.exit(__doc__)
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
        return

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


if __name__ == '__main__':
    main()

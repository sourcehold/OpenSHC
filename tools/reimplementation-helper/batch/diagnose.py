"""One page that says WHY a function does not match, and what to do next.

usage: diagnose.py NAME            (a function in the build list, after `reccmp_report.py --run`)
       diagnose.py FILE.cpp

Runs the measuring tools in the order the evidence has to be read - resolver switches, stack
frame, instruction mix, the pattern detectors, register naming - keeps the lines that matter,
and finishes with a verdict in plain words plus the command to run next. Nothing here is new
analysis: it is `slot_map.py`, `structural_diff.py`, `diff_triage.py`, `diff_jcc.py`,
`diff_signed.py`, `diff_types.py`, `diff_lea.py` and `diff_anchor.py` run for you, with the
reading rules from tools/compiler-internals/finding-mismatches.md applied to their output.

Why the order matters: the compiler is deterministic, so register names follow from the
instruction stream, which follows from the locals and the frame. A register difference that
starts AFTER the first structural difference is a symptom; chasing it directly wastes the
afternoon. The verdict names the earliest cause it can see.

Takes about half a minute (two /FA compiles). Needs a current reccmp run for the percentage
and the triage flags; everything else works from the code itself.
"""

import os
import re
import subprocess
import sys

import common

BATCH = os.path.dirname(os.path.abspath(__file__))
INTERNALS = os.path.join(os.path.dirname(os.path.dirname(BATCH)), 'compiler-internals')


def run(script, *args, where=BATCH):
    p = subprocess.run([sys.executable, os.path.join(where, script)] + list(args),
                       capture_output=True, text=True, cwd=str(common.ROOT))
    return p.stdout + p.stderr


def find_target(arg):
    """(path, short name, reccmp entry or None) for a name or a file."""
    byaddr = common.load_diff()
    for f, e, _a in common.entries(byaddr):
        f = str(f)
        name = e['name'] if e else os.path.basename(f)[:-4]
        short = name.split('::')[-1]
        if arg.endswith('.cpp'):
            if os.path.normcase(os.path.abspath(arg)) == os.path.normcase(os.path.abspath(f)):
                return f, short, e
        elif short == arg or name == arg:
            return f, short, e
    sys.exit('%s is not in the build list (cmake/openshc-sources.txt.local) or has no reccmp entry; '
             'run build_quiet.py and reccmp_report.py --run first' % arg)


def resolver_state(path):
    """How many struct resolvers are on, and whether this file's own function resolver is."""
    globals_dir = common.ROOT / 'src' / 'OpenSHC' / 'Globals'
    on = off = 0
    for h in globals_dir.glob('*.hpp'):
        t = common.read_text(h)
        on += t.count('MACRO_STRUCT_RESOLVER(') - len(re.findall(r'MACRO_STRUCT_RESOLVER\([^)]*?, false,', t))
        off += len(re.findall(r'MACRO_STRUCT_RESOLVER\([^)]*?, false,', t))
    return on, off


def section(title):
    print('')
    print('== ' + title)


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    path, short, entry = find_target(sys.argv[1])
    pct = float(entry['matching']) * 100 if entry else None
    print('%s  (%s)' % (short, common.repo_relative(path)))
    if pct is not None:
        print('reccmp %.1f%%' % pct)
    verdicts = []
    nexts = []

    # 0. the switches - with them off, every absolute address collapses to one token and the
    #    percentage is understated by up to 17 points (msvc-backend.md, "The resolver switches")
    section('0. switches')
    on, off = resolver_state(path)
    if on == 0:
        print('  struct resolvers: ALL OFF (%d). The percentage is understated; a wrong field offset'
              ' and a this-vs-global access both read as matches.' % off)
        nexts.append('python tools/reimplementation-control/enable_reimplemented_data.py  (then rebuild)')
    else:
        print('  struct resolvers: %d on, %d off' % (on, off))

    # 1. the frame
    section('1. stack frame (slot_map.py)')
    out = run('slot_map.py', path)
    m = re.search(r'^frame\s+original (0x[0-9a-f]+|\d+)\s+ours (0x[0-9a-f]+|\d+)\s+\(([-+]\d+)\)', out, re.M)
    frame_delta = None
    if m:
        frame_delta = int(m.group(3))
        print('  ' + m.group(0))
        regime = re.search(r'^regime\s+(.*)$', out, re.M)
        if regime:
            print('  regime: ' + regime.group(1))
        if frame_delta < 0:
            verdicts.append('FRAME: ours is %d bytes smaller - we are MISSING a local the original has. '
                            'No instruction or register work can fix this first.' % -frame_delta)
            nexts.append('python tools/reimplementation-helper/batch/slot_map.py %s   # the ? rows name the slot; the decompile usually names the local' % common.repo_relative(path))
        elif frame_delta > 0:
            verdicts.append('FRAME: ours is %d bytes larger - a surplus local, or a value the original keeps in a register. '
                            'Check the lowest-reference extra slot first.' % frame_delta)
            nexts.append('python tools/reimplementation-helper/batch/diff_slots.py %s' % short)
        else:
            print('  frame sizes agree')
        for l in out.splitlines():
            if l.strip().startswith('?') or re.match(r'\s+\?\s', l):
                print('  ' + l.rstrip())
    else:
        warn = [l for l in out.splitlines() if 'warn' in l.lower() or 'cannot' in l.lower()]
        print('  ' + (warn[0].strip() if warn else 'no frame comparison (see slot_map.py output)'))

    # 2. the instruction mix and order
    section('2. instructions (structural_diff.py)')
    out = run('structural_diff.py', short)
    kind = delta = None
    for key in ('instructions', 'kind', 'delta'):
        m = re.search(r'^\s+%s\s+(.*)$' % key, out, re.M)
        if m:
            print('  %s %s' % (key, m.group(1).split('<-')[0].strip()))
            if key == 'kind':
                kind = float(m.group(1).split()[0])
            if key == 'delta':
                delta = int(m.group(1).split()[0])
    dups = re.findall(r'DUPLICATION: (.*?)\n((?:\s{6}.*\n)+)', out)
    for head, body in dups:
        print('  DUPLICATION: ' + head.strip())
        for l in body.rstrip().splitlines():
            print('      ' + l.strip())
    pol = re.search(r'POLARITY: (.*)', out)
    if pol:
        print('  POLARITY: ' + pol.group(1))
    mix = re.search(r'mnemonic original ours\s*\n((?:\s+\w+\s+\d+\s+\d+\s+[-+]\d+\n?)+)', out)
    if mix:
        for l in mix.group(1).rstrip().splitlines():
            print('    ' + l.strip())
    regs = re.search(r'registers: (\d+) operand', out)
    first = re.search(r'first STRUCTURAL difference is at original instruction (\d+) and the first\s+REGISTER difference at (\d+)', out)
    cycle = 'closed cycle' in out
    if delta is not None and delta > 0:
        if dups:
            which = 'the original duplicates a run we share' if 'original computes' in dups[0][0] else 'we duplicate a run the original shares'
            verdicts.append('MIX: %d mismatched instruction(s); %s. Share in the source exactly the prefix the '
                            'original shares (an index in a local) and write the rest out per arm.' % (delta, which))
        else:
            verdicts.append('MIX: %d mismatched instruction(s) - a real code-shape defect (see the mnemonic table).' % delta)
        nexts.append('python tools/compiler-internals/tuple_dump.py %s --name %s --diff codegen postlower   # IL vs lowered: is the extra/missing instruction already in the IL?' % (common.repo_relative(path), short))
    elif kind is not None and kind < 0.99:
        verdicts.append('ORDER: same instructions in a different order. Statement order MAY be the lever (it was for '
                        'setAICParameters_NN) but the scheduler also reorders freely; measure every move.')
        nexts.append('python tools/compiler-internals/tuple_dump.py %s --name %s --diff final preencode   # if the order appears here, it is the late tail-merge/code-motion, not your statements' % (common.repo_relative(path), short))
        nexts.append('python tools/reimplementation-helper/batch/quick_reorder.py %s START END -s' % common.repo_relative(path))
    elif kind is not None:
        if regs:
            verdicts.append('ALLOCATION: same instructions, same order; %s operands differ only in register name%s.'
                            % (regs.group(1), ' (a closed cycle - the allocation is structurally right)' if cycle else ''))
            nexts.append('python tools/compiler-internals/reg_scores.py %s --whyreg LOCAL   # read the key gap of the swapped pair; a gap of a few units is one statement move, tens of units is unreachable' % common.repo_relative(path))
        else:
            verdicts.append('STRUCTURALLY PERFECT below 100: the cause is outside the function (a resolver, a header, the build). '
                            'If other functions stop on the same percentage, it is shared.')
    if pol and delta == 0:
        verdicts.append('POLARITY flip with delta 0: either our arms are the other way round (swap them) or the late '
                        'tail merge kept the other copy - tuple_dump.py --diff final preencode tells which.')
    if first:
        a, b = int(first.group(1)), int(first.group(2))
        print('  first structural difference at %d, first register difference at %d -> registers are %s'
              % (a, b, 'a symptom' if b >= a else 'the earlier problem'))

    # 3. the triage flags from the last reccmp run
    section('3. triage flags (diff_triage.py)')
    out = run('diff_triage.py', short)
    rows = [l for l in out.splitlines() if l.strip().startswith(short) or 'ret [' in l]
    for l in rows:
        print('  ' + l.rstrip())
        if 'BYTE' in l:
            verdicts.append('BYTE: we have byte-sized stack slots the original does not - a bool/char local that is an int in the original.')
        if ' RET' in l:
            verdicts.append('RET: an early-return block sits in a different place. The original outlines the cold case; '
                            'the 2+2 guard shape and the late epilogue fold decide it (msvc-backend.md, early-exit epilogue wall).')

    # 4. the pattern detectors - each names a concrete source edit
    section('4. detectors')
    for script, what in (('diff_jcc.py', 'comparison one strictness step off, or operands swapped'),
                         ('diff_signed.py', 'signed vs unsigned comparison - compare through (int)'),
                         ('diff_types.py', 'movsx vs movzx (field signedness) or add vs sub (formula sign)'),
                         ('diff_lea.py', 'lea where the original does a destructive add - drop the snapshot local'),
                         ('diff_anchor.py', 'loop base anchored on a different field')):
        out = run(script, short)
        body = [l for l in out.splitlines() if l.strip() and not l.startswith('#')
                and 'warning' not in l.lower() and 'Re-build' not in l]
        # every detector ends with a count line; "0 ..." means it found nothing
        summary = body[-1].strip() if body else '0'
        if body and not summary.startswith('0 ') and not summary.startswith('no '):
            print('  %s: %s' % (script, what))
            for l in body[:8]:
                print('      ' + l.rstrip())
            nexts.append('python tools/reimplementation-helper/batch/%s %s' % (script, short))
        else:
            print('  %s: nothing' % script)

    # the verdict
    section('verdict')
    if not verdicts:
        print('  nothing structural found - see the raw tool output above')
    for v in verdicts:
        print('  * ' + v)
    section('next')
    seen = set()
    for n in nexts:
        if n not in seen:
            print('  ' + n)
            seen.add(n)
    print('  python tools/reimplementation-helper/batch/quick_diff.py %s   # 6 s per source variant; confirm with reccmp_report.py --run' % common.repo_relative(path))


if __name__ == '__main__':
    main()

#!/usr/bin/env python
"""Read the original's translation-unit layout off its function addresses, and list the call pairs that need it.

    python tools/compiler-internals/tu_layout.py runs [ADDR]        # class runs in address order (around ADDR)
    python tools/compiler-internals/tu_layout.py pairs [LISTFILE]   # caller -> callee pairs among the /GL files
    python tools/compiler-internals/tu_layout.py around NAME        # the run that holds NAME, and NAME's callees

The linker keeps each object's functions together and in definition order (no /ORDER file, no PGO), so a run of
consecutive addresses whose functions belong to one class or one family is one translation unit of the original.
Addresses and names come from the `MACRO_FUNCTION_RESOLVER(..., Address::SHC_..., &Class::name)` entries of every
`*.func.hpp`, so the picture covers the functions the project has declared; gaps are undeclared code.

`pairs` reads `cmake/compiler-flags-gl.txt` (or LISTFILE), finds every `MACRO_CALL(...)` /
`MACRO_CALL_MEMBER(...)` target in those files, and prints caller, callee, whether both are in the list, the
callee's address, and whether caller and callee sit in the same address run. Those are the functions where
the original compiler knew the callee's register usage - which it also does without /GL when both are in one
translation unit (see msvc-backend.md, "The /GL conundrum").
"""
import glob
import io
import os
import re
import sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
RES = re.compile(r'MACRO_FUNCTION_RESOLVER(?:_EXT)?\(\s*([^,]+(?:\([^)]*\))?[^,]*),\s*(true|false),\s*'
                 r'Address::SHC_3BB0A8C1_(0x[0-9A-Fa-f]+),\s*&?([\w:]+)', re.S)


def resolvers():
    """[(addr, Class, name, func.hpp path)] sorted by address."""
    out = []
    for p in glob.glob(os.path.join(ROOT, 'src', 'OpenSHC', '**', '*.func.hpp'), recursive=True):
        s = io.open(p, encoding='utf-8', errors='replace').read()
        for m in RES.finditer(s):
            full = m.group(4)
            cls, _, name = full.rpartition('::')
            out.append((int(m.group(3), 16), cls or '-', name, os.path.relpath(p, ROOT).replace(os.sep, '/')))
    out.sort()
    return out


def runs(entries):
    """Group consecutive entries by class; [(cls, first, last, [entries])]."""
    out = []
    for e in entries:
        if out and out[-1][0] == e[1]:
            out[-1][3].append(e)
        else:
            out.append([e[1], e[0], e[0], [e]])
    return [(c, es[0][0], es[-1][0], es) for c, a, b, es in out]


def find_impl(name):
    """Path of the .cpp that defines NAME (first match)."""
    hits = glob.glob(os.path.join(ROOT, 'src', 'OpenSHC', '**', name + '.cpp'), recursive=True)
    return hits[0] if hits else None


def callees_of(path):
    s = io.open(path, encoding='utf-8', errors='replace').read()
    return sorted(set(re.findall(r'MACRO_CALL(?:_MEMBER)?\(\s*(?:[\w:]+::)?(\w+)\s*[,)]', s)))


def cmd_runs(entries, near=None):
    rs = runs(entries)
    if near is not None:
        rs = [r for r in rs if r[1] - 0x4000 <= near <= r[2] + 0x4000]
    for cls, a, b, es in rs:
        print('%08x-%08x  %-40s %3d fn  %s' % (a, b, cls, len(es), ', '.join(e[2] for e in es)[:90]))


def cmd_around(entries, name):
    by_name = {e[2]: e for e in entries}
    if name not in by_name:
        sys.exit('no resolver named ' + name)
    me = by_name[name]
    for cls, a, b, es in runs(entries):
        if a <= me[0] <= b:
            print('run %08x-%08x %s (%d functions):' % (a, b, cls, len(es)))
            for e in es:
                print('   %08x %s%s' % (e[0], e[2], '   <--' if e is me else ''))
    impl = find_impl(name)
    if impl:
        print('callees of %s (from %s):' % (name, os.path.relpath(impl, ROOT)))
        for c in callees_of(impl):
            e = by_name.get(c)
            print('   %-45s %s' % (c, '%08x %s' % (e[0], e[1]) if e else '(no resolver)'))


def cmd_pairs(entries, listfile):
    by_name = {e[2]: e for e in entries}
    rs = runs(entries)

    def run_of(addr):
        for i, (cls, a, b, es) in enumerate(rs):
            if a <= addr <= b:
                return i
        return None

    files = [l.strip() for l in io.open(listfile, encoding='utf-8') if l.strip() and not l.startswith('#')]
    names = set(os.path.splitext(os.path.basename(f))[0] for f in files)
    print('%-8s %-44s %-8s %-42s %-7s %-8s %s' % ('caller', '', 'callee', '', 'in list', 'same run', 'callee earlier'))
    for f in files:
        caller = os.path.splitext(os.path.basename(f))[0]
        p = os.path.join(ROOT, f)
        if not os.path.exists(p):
            print('%-48s (file missing)' % caller)
            continue
        ce = by_name.get(caller)
        for c in callees_of(p):
            e = by_name.get(c)
            same = '?' if not (ce and e) else ('yes' if run_of(ce[0]) == run_of(e[0]) else 'no')
            # the backend emits callees before their callers (order_probe.py), so inside one translation
            # unit the callee's address is the lower one; a callee *above* its caller is in another unit
            earlier = '?' if not (ce and e) else ('yes' if e[0] < ce[0] else 'NO')
            print('%08x %-44s %08x %-42s %-7s %-8s %s' % (ce[0] if ce else 0, caller, e[0] if e else 0, c,
                                                        'yes' if c in names else '', same, earlier))


def cmd_calls(entries, verbose):
    """Every caller -> callee pair the reimplemented sources know, and whether the callee sits below the caller."""
    pairs = call_pairs(entries)
    below = [x for x in pairs if x[2] < x[0]]
    print('%d call pairs with a resolved callee; callee below caller: %d (%.0f%%), above: %d' % (
        len(pairs), len(below), 100.0 * len(below) / max(1, len(pairs)), len(pairs) - len(below)))
    print('within 64 KB and below: %d; above and within 64 KB: %d' % (
        sum(1 for x in below if x[0] - x[2] < 0x10000), sum(1 for x in pairs if 0 < x[2] - x[0] < 0x10000)))
    if verbose:
        print('%-8s %-40s %-8s %-40s %s' % ('caller', '', 'callee', '', 'callee - caller'))
        for caller, cn, callee, c in sorted(pairs):
            print('%08x %-40s %08x %-40s %+d' % (caller, cn, callee, c, callee - caller))


def call_pairs(entries):
    by_name = {e[2]: e for e in entries}
    pairs = []
    for p in glob.glob(os.path.join(ROOT, 'src', 'OpenSHC', '**', '*.cpp'), recursive=True):
        s = io.open(p, encoding='utf-8', errors='replace').read()
        for m in re.finditer(r'FUNCTION: STRONGHOLDCRUSADER (0x[0-9A-Fa-f]+)[^\n]*\n[^\n(]*?(?:(\w+)::)?(\w+)\(', s):
            caller = int(m.group(1), 16)
            body_end = s.find('\n    // FUNCTION:', m.end())
            body = s[m.end():body_end if body_end > 0 else len(s)]
            for c in sorted(set(re.findall(r'MACRO_CALL(?:_MEMBER)?\(\s*(?:[\w:]+::)?(\w+)\s*[,)]', body))):
                e = by_name.get(c)
                if e and e[0] != caller:
                    pairs.append((caller, m.group(3), e[0], c))
    return pairs


def cmd_units(entries):
    """Cut the address space into translation units: every upward call (callee above its caller) must cross a
    unit boundary, so the fewest cuts that stab all such [caller, callee] intervals is a lower bound on the
    units, and each cut lands in the gap the intervals share. Downward calls say nothing (they may be in one
    unit or not); a unit printed here may therefore still be several units."""
    pairs = call_pairs(entries)
    up = sorted(((a, b) for a, _, b, _ in pairs if b > a), key=lambda x: x[1])
    cuts = []
    last = -1
    for a, b in up:
        if a >= last:
            # the cut goes just below the callee: the lowest right endpoint stabs every interval open here
            last = b
            cuts.append(b)
    addrs = [e[0] for e in entries]
    names = {e[0]: e for e in entries}
    print('%d upward call pairs need at least %d unit boundaries\n' % (len(up), len(cuts)))
    lo = addrs[0]
    bounds = cuts + [addrs[-1] + 1]
    for cut in bounds:
        members = [a for a in addrs if lo <= a < cut]
        if not members:
            lo = cut
            continue
        classes = {}
        for a in members:
            classes[names[a][1]] = classes.get(names[a][1], 0) + 1
        top = sorted(classes.items(), key=lambda kv: -kv[1])[:6]
        print('%08x-%08x  %4d fn  %2d classes  %s' % (members[0], members[-1], len(members), len(classes),
                                                     ', '.join('%s x%d' % kv for kv in top)))
        lo = cut


def main(argv):
    if not argv:
        print(__doc__)
        return 2
    entries = resolvers()
    if argv[0] == 'units':
        cmd_units(entries)
    elif argv[0] == 'calls':
        cmd_calls(entries, '-v' in argv)
    elif argv[0] == 'runs':
        cmd_runs(entries, int(argv[1], 16) if len(argv) > 1 else None)
    elif argv[0] == 'around':
        cmd_around(entries, argv[1])
    elif argv[0] == 'pairs':
        cmd_pairs(entries, argv[1] if len(argv) > 1 else os.path.join(ROOT, 'cmake', 'compiler-flags-gl.txt'))
    else:
        print(__doc__)
        return 2
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))

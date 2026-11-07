#!/usr/bin/env python
"""Build the translation-unit layouts of a caller and its callee(s), and diff each against the original.

    python tools/compiler-internals/tu_merge.py CALLER.cpp CALLEE.cpp [CALLEE2.cpp ...] [--keep]
    python tools/compiler-internals/tu_merge.py --batch [LISTFILE]      # every pair of cmake/compiler-flags-gl.txt

Writes three scratch files under build-RelWithDebInfo/batch/variants/tu_<caller>/ and runs quick_diff.py on
the caller in each:

    caller_only.cpp     the caller as committed: every callee is in another translation unit
    callees_first.cpp   the callees' bodies pasted into the caller's file, before the caller
    caller_first.cpp    the same, after the caller

The committed sources are not touched. The callees' resolvers must be switched on (their `MACRO_FUNCTION_RESOLVER`
flag `true`), or the compiler never sees a direct call. A callee from another namespace is pasted inside its own
namespace chain, outside the caller's. What the three numbers mean is in msvc-backend.md under "The /GL
conundrum": without /GL the compiler knows which registers a callee leaves alone only when the callee is compiled
in the same translation unit, and then in either order.

`--batch` runs every caller of the /GL list against each of its resolvable callees, then against all of them at
once: `this` has to survive every call in a row before the spill disappears, so a caller with several callees in
its unit may only move on the ALL row.
"""
import io
import os
import re
import subprocess
import sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
QD = os.path.join(ROOT, 'tools', 'reimplementation-helper', 'batch', 'quick_diff.py')
MARK = re.compile(r'^[ \t]*// FUNCTION: STRONGHOLDCRUSADER 0x[0-9A-Fa-f]+[^\n]*\n', re.M)


def read(p):
    return io.open(p, encoding='utf-8').read().replace('\r\n', '\n')


def absolute_includes(s, srcdir):
    """Rewrite `#include "../X.hpp"` relative includes into paths from src/, so the text works from anywhere."""
    def fix(m):
        rel = m.group(1)
        if rel.startswith('.'):
            p = os.path.normpath(os.path.join(srcdir, rel))
            rel = os.path.relpath(p, os.path.join(ROOT, 'src')).replace(os.sep, '/')
        return '#include "%s"' % rel
    return re.sub(r'#include "([^"]+)"', fix, s)


def split(s):
    """(head, [function blocks], tail): a block is a marker line plus the definition through its closing brace."""
    marks = list(MARK.finditer(s))
    if not marks:
        sys.exit('no `// FUNCTION:` marker')
    head = s[:marks[0].start()]
    blocks = []
    for i, m in enumerate(marks):
        start = m.start()
        # the preceding comment lines belong to the function
        while True:
            prev = s.rfind('\n', 0, start - 1)
            line = s[prev + 1:start]
            if line.strip().startswith('//'):
                start = prev + 1
            else:
                break
        body_at = s.index('{', m.end())
        depth = 0
        j = body_at
        while True:
            c = s[j]
            if c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
                if depth == 0:
                    break
            j += 1
        end = s.index('\n', j) + 1
        blocks.append(s[start:end])
        if i == 0:
            head = s[:start]
    tail = s[end:]
    return head, blocks, tail


def namespaces(head):
    return re.findall(r'^\s*namespace\s+(\w+)\s*\{', head, re.M)


def measure(caller, callees, keep=False, quiet=False):
    """Write the three layouts for one caller and its callee files; return {label: ratio}."""
    cs = read(caller)
    cs = absolute_includes(cs, os.path.dirname(os.path.abspath(caller)))
    head, cblocks, tail = split(cs)
    ns = namespaces(head)
    extra_includes = []
    extra_using = []
    pasted = []      # callee blocks that live in the caller's own namespace chain
    foreign = []     # (namespace chain, using lines, blocks) for callees of another namespace
    for p in callees:
        s = absolute_includes(read(p), os.path.dirname(os.path.abspath(p)))
        h, blocks, _ = split(s)
        extra_includes += [l for l in re.findall(r'^#include "[^"]+"', h, re.M) if l not in head]
        usings = [l.strip() for l in re.findall(r'^[ \t]*using [^\n]+;', h, re.M)]
        if namespaces(h) == ns:
            extra_using += [l for l in usings if l not in head]
            pasted += blocks
        else:
            foreign.append((namespaces(h), usings, blocks))
    inc_at = head.rfind('#include')
    inc_end = head.index('\n', inc_at) + 1 if inc_at >= 0 else 0
    head2 = head[:inc_end] + ''.join(l + '\n' for l in extra_includes) + head[inc_end:]
    # `using` lines go right after the last namespace opener
    last_ns = list(re.finditer(r'^\s*namespace\s+\w+\s*\{[^\n]*\n', head2, re.M))[-1].end()
    head2 = head2[:last_ns] + ''.join(l + '\n' for l in extra_using) + ('\n' if extra_using else '') + head2[last_ns:]
    # a callee from another namespace gets its own chain, closed again, outside the caller's
    wrapped = ''
    for chain, usings, blocks in foreign:
        wrapped += ''.join('namespace %s {\n' % n for n in chain) + ''.join(l + '\n' for l in usings) + '\n'
        wrapped += '\n'.join(blocks) + '\n' + '}\n' * len(chain) + '\n'
    first_ns = re.search(r'^\s*namespace\s+\w+\s*\{', head2, re.M).start()
    includes, head_ns = head2[:first_ns], head2[first_ns:]
    name = os.path.splitext(os.path.basename(caller))[0]
    out = os.path.join(ROOT, 'build-RelWithDebInfo', 'batch', 'variants', 'tu_' + name)
    os.makedirs(out, exist_ok=True)
    body = ''.join(cblocks)
    paste = '\n'.join(pasted)
    variants = [
        ('caller_only', includes + head_ns + body + tail),
        ('callees_first', includes + wrapped + head_ns + paste + '\n' + body + tail),
        ('caller_first', includes + head_ns + body + '\n' + paste + tail + '\n' + wrapped),
    ]
    fn = re.search(r'(?:\w+::)?(\w+)\(', cblocks[0][MARK.search(cblocks[0]).end():]).group(1)
    ratios = {}
    for label, text in variants:
        p = os.path.join(out, label + '.cpp')
        io.open(p, 'w', encoding='utf-8', newline='\n').write(text)
        r = subprocess.run([sys.executable, QD, p, '--name', fn], capture_output=True, text=True, cwd=ROOT)
        first = (r.stdout.strip().splitlines() or [r.stderr.strip()[-300:]])[0]
        m = re.search(r'ratio ([0-9.]+)', first)
        ratios[label] = float(m.group(1)) if m else None
        if not quiet:
            print('%-14s %s' % (label, first.replace('##### %s.cpp  ' % label, '')))
        if keep:
            print(r.stdout)
    if not quiet:
        print('variants in', os.path.relpath(out, ROOT))
    return ratios


def batch(listfile):
    """Every caller -> callee pair of the /GL list (tu_layout.py pairs) whose two files exist, measured."""
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import tu_layout
    entries = tu_layout.resolvers()
    by_name = {e[2]: e for e in entries}
    files = [l.strip() for l in io.open(listfile, encoding='utf-8') if l.strip() and not l.startswith('#')]
    print('%-44s %-44s %-7s %-7s %-7s %s' % ('caller', 'callee', 'only', 'first', 'after', 'verdict'))
    for f in files:
        caller = os.path.join(ROOT, f)
        if not os.path.exists(caller):
            continue
        cname = os.path.splitext(os.path.basename(f))[0]
        found = [(c, tu_layout.find_impl(c)) for c in tu_layout.callees_of(caller) if c in by_name]
        found = [(c, p) for c, p in found if p]
        # one callee at a time, then all of them that sit *below* the caller in the image together: inside
        # one unit the callee is always the lower address (bottom-up emission), and `this` has to survive
        # every call in a row for the spill to go, so a caller with several unit-mates may move only on
        # the last row. A callee from above is left out: merged, it only gets inlined and hurts.
        ce = by_name.get(cname)
        below = [(c, p) for c, p in found if ce and by_name[c][0] < ce[0]]
        trials = [(c, [p]) for c, p in found]
        if len(below) > 1:
            trials.append(('ALL %d callees below' % len(below), [p for _, p in below]))
        for label, paths in trials:
            try:
                r = measure(caller, paths, quiet=True)
            except Exception as e:
                print('%-44s %-44s %s' % (cname, label, str(e)[-80:]))
                continue
            only, first, after = r['caller_only'], r['callees_first'], r['caller_first']
            if None in (only, first, after):
                verdict = 'compile error'
            elif first > only + 1e-9:
                verdict = 'SAME UNIT: gains %+.4f' % (first - only)
            elif first < only - 1e-9:
                verdict = 'OTHER UNIT: knowing this callee changes the allocation; the original did not know it'
            else:
                verdict = 'no effect'
            print('%-44s %-44s %-7s %-7s %-7s %s' % (cname, label, only, first, after, verdict), flush=True)


def main(argv):
    keep = '--keep' in argv
    argv = [a for a in argv if a != '--keep']
    if argv and argv[0] == '--batch':
        batch(argv[1] if len(argv) > 1 else os.path.join(ROOT, 'cmake', 'compiler-flags-gl.txt'))
        return 0
    if len(argv) < 2:
        print(__doc__)
        return 2
    caller, callees = argv[0], argv[1:]
    try:
        measure(caller, callees, keep=keep)
    except ValueError as e:
        sys.exit(str(e))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))

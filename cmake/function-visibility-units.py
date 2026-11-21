"""Generate the translation units that cmake/function-visibility.txt asks for.

    python cmake/function-visibility-units.py ROOT MANIFEST SOURCES_LIST OUT_DIR

Called by CMakeLists.txt when OPENSHC_FUNCTION_VISIBILITY_UNITS is ON. The manifest lists, per caller, the callees
whose bodies the caller must see when it is compiled. A function can be defined only once, so every caller and callee
joined by an entry ends up in one group, and each group becomes one wrapper file that #includes its members' .cpp
files. The build then compiles the wrappers instead of the members, and the members leave the /GL list.

ROOT          the source tree (CMAKE_SOURCE_DIR)
MANIFEST      cmake/function-visibility.txt
SOURCES_LIST  a file with the build's OpenSHC sources, one per line, as CMake has them
OUT_DIR       where the wrappers and units.cmake are written (in the build tree)

units.cmake sets OPENSHC_VISIBILITY_UNIT_FILES (the wrappers) and OPENSHC_VISIBILITY_MEMBER_FILES (the sources they
replace, spelled as in SOURCES_LIST). Only sources in the build are grouped; an entry whose caller or callee is not
in the build simply has no effect.

Two things would break a wrapper:
- a .cpp included twice: groups are formed over files, not functions, so a file that defines several listed
  functions lands in exactly one group;
- two members defining the same internal-linkage name (a file-scope `static`, or anything in an anonymous
  namespace): such a group is not wrapped, its files build as before, and the clash is printed. The check reads the
  source line by line rather than parsing it, so a `{` or `}` inside a string literal or a comment can hide a
  static from it. A clash it misses is not silent: the wrapper then fails to compile (C2084, function already has a
  body).

Names in the manifest that no .cpp in the build defines are skipped, and their count and names are printed.
"""
import io
import os
import re
import sys

MARK = re.compile(r'// FUNCTION: STRONGHOLDCRUSADER 0x[0-9A-Fa-f]+[^\n]*\n')
NAMESPACE = re.compile(r'namespace\s+(\w+)\s*\{|(\{)|\}')


def read(path):
    return io.open(path, encoding='utf-8', errors='replace').read()


def defined_names(text):
    """Fully qualified names of the functions marked in TEXT, as the definitions spell them."""
    names = []
    for m in MARK.finditer(text):
        stack = []  # namespace name, or None for any other brace
        for t in NAMESPACE.finditer(text, 0, m.start()):
            if t.group(1) or t.group(2):
                stack.append(t.group(1))
            elif stack:
                stack.pop()
        d = re.search(r'([\w:]+)\s*\(', text[m.end():])
        if d:
            names.append('::'.join([n for n in stack if n] + [d.group(1)]))
    return names


def internal_names(text):
    """Names with internal linkage defined at file scope: `static` definitions directly inside namespaces, and
    whatever an anonymous namespace defines at its own top level. Comments and strings are not stripped: a false
    hit only makes a group fall back to separate files, and a brace inside one can hide a name (see the module
    docstring)."""
    names = set()
    stack = []  # one entry per open brace: 'ns', 'anon' or 'block'
    decl = re.compile(r'^(?:static\s+)?(?:[\w:<>,*&]+\s+)+[*&]*(\w+)\s*(?:\(|=|\[|;)')
    for raw in text.splitlines():
        line = raw.strip()
        if line.startswith(('//', '#')):
            continue
        at_ns_scope = all(k in ('ns', 'anon') for k in stack)
        if at_ns_scope:
            m = decl.match(line)
            if m and (line.startswith('static') or (stack and stack[-1] == 'anon')):
                names.add(m.group(1))
        for tok in re.finditer(r'namespace\s+\w+\s*\{|namespace\s*\{|\{|\}', line):
            t = tok.group(0)
            if t == '}':
                if stack:
                    stack.pop()
            elif t.startswith('namespace'):
                stack.append('anon' if re.match(r'namespace\s*\{', t) else 'ns')
            else:
                stack.append('block')
    return names


def main(argv):
    root, manifest, sources_list, out_dir = argv
    root = os.path.abspath(root)
    sources = [l.strip() for l in io.open(sources_list, encoding='utf-8') if l.strip()]

    def key(path):
        return os.path.normcase(os.path.abspath(os.path.join(root, path)))
    in_build = dict((key(s), s) for s in sources)

    where = {}  # qualified name -> source entry
    for d, _, files in os.walk(os.path.join(root, 'src', 'OpenSHC')):
        for f in files:
            if f.endswith('.cpp'):
                p = os.path.join(d, f)
                if os.path.normcase(os.path.abspath(p)) in in_build:
                    for n in defined_names(read(p)):
                        where.setdefault(n, in_build[os.path.normcase(os.path.abspath(p))])

    entries, cur = [], None
    for number, line in enumerate(io.open(manifest, encoding='utf-8'), 1):
        if not line.strip():
            continue
        if line.startswith((' ', '\t')):
            if cur is None:
                sys.exit('%s:%d: an indented callee before any caller; each entry starts with an unindented caller'
                         % (manifest, number))
            cur[1].append(line.strip())
        else:
            cur = (line.strip(), [])
            entries.append(cur)

    parent = {}

    def find(x):
        parent.setdefault(x, x)
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x
    missing = set()
    for caller, callees in entries:
        missing.update(n for n in [caller] + callees if n not in where)
        if caller not in where:
            continue
        for c in callees:
            if c in where and where[c] != where[caller]:
                parent[find(where[caller])] = find(where[c])
    if missing:
        print('function-visibility: %d names have no .cpp in this build and are skipped: %s'
              % (len(missing), ', '.join(sorted(missing))))
    groups = {}
    for f in list(parent):
        groups.setdefault(find(f), []).append(f)

    if not os.path.isdir(out_dir):
        os.makedirs(out_dir)
    units, members = [], []
    order = dict((s, i) for i, s in enumerate(sources))
    for g in sorted((sorted(g, key=order.get) for g in groups.values()), key=lambda g: order[g[0]]):
        seen, clash = {}, []
        for f in g:
            for n in internal_names(read(os.path.join(root, f))):
                if n in seen:
                    clash.append('%s (%s and %s)' % (n, seen[n], f))
                seen.setdefault(n, f)
        if clash:
            print('function-visibility: not grouping %d files, internal names clash: %s' % (len(g), '; '.join(clash)))
            continue
        path = os.path.join(out_dir, 'unit_%03d.cpp' % len(units)).replace(os.sep, '/')
        text = '// Generated from cmake/function-visibility.txt by cmake/function-visibility-units.py. Do not edit.\n'
        text += ''.join('#include "%s"\n' % os.path.join(root, f).replace(os.sep, '/') for f in g)
        if not os.path.exists(path) or read(path) != text:  # unchanged wrappers keep their timestamps
            io.open(path, 'w', encoding='utf-8', newline='\n').write(text)
        units.append(path)
        members.extend(g)
    with io.open(os.path.join(out_dir, 'units.cmake'), 'w', encoding='utf-8', newline='\n') as o:
        o.write('set(OPENSHC_VISIBILITY_UNIT_FILES\n%s)\n' % ''.join('    "%s"\n' % u for u in units))
        o.write('set(OPENSHC_VISIBILITY_MEMBER_FILES\n%s)\n' % ''.join('    "%s"\n' % m for m in members))
    print('function-visibility: %d units holding %d source files' % (len(units), len(members)))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))

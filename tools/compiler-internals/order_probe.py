#!/usr/bin/env python
"""Show the order in which cl 14.00 /O2 emits the functions of one translation unit, and link.exe lays objects out.

    python tools/compiler-internals/order_probe.py

Generates a translation unit with three classes whose methods call each other at call depths 0, 1 and 2, written
in an order that is neither by class nor by depth, compiles it with the project's flags (/O2, which includes /Gy)
and prints the order of the `PROC` lines in the /FA listing. Then compiles a second copy, links both into a DLL
with /MAP, and prints the function order in the image. The answer explains the repeating class cycles that
`tu_layout.py runs` shows in the original: the backend emits a translation unit bottom-up, every function after
the functions it calls, so one big source file with N classes comes out as "all leaves, then their callers, ...".
"""
import io
import os
import re
import subprocess
import sys

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
TC = os.path.join(ROOT, 'MSVC1400-SP1')
OUT = os.path.join(ROOT, 'build-RelWithDebInfo', 'batch', 'order_probe')

SRC = r'''
struct A { int v[64]; int leaf(); int mid(); int top(); };
struct B { int v[64]; int leaf(); int mid(); int top(); };
struct C { int v[64]; int leaf(); int mid(); int top(); };
extern "C" int __declspec(noinline) sink(int);

// source order: tops first, then mids, then leaves, classes interleaved
int A::top()  { return sink(mid() + 1); }
int B::top()  { return sink(mid() + 2); }
int C::top()  { return sink(mid() + 3); }
int A::mid()  { int s = 0; for (int i = 0; i < 64; i++) s += v[i] * leaf(); return sink(s); }
int B::mid()  { int s = 0; for (int i = 0; i < 64; i++) s += v[i] * leaf(); return sink(s); }
int C::mid()  { int s = 0; for (int i = 0; i < 64; i++) s += v[i] * leaf(); return sink(s); }
int A::leaf() { int s = 0; for (int i = 0; i < 64; i++) s += v[i] * v[63 - i]; return s; }
int B::leaf() { int s = 0; for (int i = 0; i < 64; i++) s += v[i] * v[63 - i]; return s; }
int C::leaf() { int s = 0; for (int i = 0; i < 64; i++) s += v[i] * v[63 - i]; return s; }
'''


def run(args, cwd):
    env = dict(os.environ)
    env['PATH'] = os.path.join(TC, 'VC', 'bin') + os.pathsep + os.path.join(TC, 'Common7', 'IDE') + os.pathsep + env['PATH']
    env['INCLUDE'] = os.path.join(TC, 'VC', 'include')
    env['LIB'] = os.path.join(TC, 'VC', 'lib')
    r = subprocess.run(args, cwd=cwd, env=env, capture_output=True, text=True)
    if r.returncode:
        print(r.stdout[-2000:], r.stderr[-2000:])
        sys.exit(1)
    return r.stdout


def procs(asm):
    return [re.sub(r'@.*', '', l.split()[0]).lstrip('?') + '/' + re.search(r'; (\S+)', l).group(1)
            for l in asm.splitlines() if re.match(r'^\S+ PROC', l)]


def main():
    os.makedirs(OUT, exist_ok=True)
    cl = os.path.join(TC, 'VC', 'bin', 'cl.exe')
    link = os.path.join(TC, 'VC', 'bin', 'link.exe')
    for name, flags in (('o2', ['/O2']), ('o2_noinline', ['/O2', '/Ob0']), ('od', ['/Od'])):
        io.open(os.path.join(OUT, name + '.cpp'), 'w').write(
            'namespace %s {\n%s\n}\n' % (name, SRC.replace('sink', 'sink_' + name)))
        run([cl, '/nologo', '/c', '/FA', '/GS-'] + flags + ['/Fo' + name + '.obj', '/Fa' + name + '.asm', name + '.cpp'], OUT)
        order = procs(io.open(os.path.join(OUT, name + '.asm'), errors='replace').read())
        print('%-12s %s' % (name, '  '.join(p.split('/')[1] for p in order)))
    # two objects into one image: does the linker keep object order?
    io.open(os.path.join(OUT, 'sinks.c'), 'w').write(
        'int sink_o2(int x){return x;} int sink_o2_noinline(int x){return x;} int sink_od(int x){return x;}\n')
    run([cl, '/nologo', '/c', '/O2', '/GS-', 'sinks.c'], OUT)
    # /OPT:NOREF keeps the unreferenced COMDATs of the /O2 objects (a release link drops them otherwise)
    run([link, '/nologo', '/dll', '/noentry', '/nodefaultlib', '/map:probe.map', '/out:probe.dll',
         '/opt:noref', '/opt:noicf', '/export:sink_o2', 'od.obj', 'o2.obj', 'o2_noinline.obj', 'sinks.obj'], OUT)
    txt = io.open(os.path.join(OUT, 'probe.map'), errors='replace').read()
    rows = re.findall(r'^ 0001:([0-9a-f]{8})\s+(\S+)\s+[0-9a-f]+ f\s+(\S+)', txt, re.M)
    print('image order (link order od, o2, o2_noinline, sinks):')
    for rva, sym, obj in sorted(rows):
        m = re.search(r'; (\S+)', sym)
        print('   %s  %-14s %s' % (rva, obj, sym[:60]))


if __name__ == '__main__':
    main()

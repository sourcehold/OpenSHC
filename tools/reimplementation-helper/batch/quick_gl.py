"""quick_diff for files in cmake/compiler-flags-gl.txt: compile ONE file with /GL, LTCG-link it with its callees.

usage: quick_gl.py FILE.cpp [CALLEE.cpp ...] [-q] [-s]

quick_diff.py compiles without /GL, so it cannot show what LTCG buys a caller - typically a volatile register
(ecx/edx) kept alive across a call to a callee that is known not to touch it. This compiles FILE with the /GL
command line of the build, links it with /LTCG into a throw-away DLL (/NOENTRY /FORCE:UNRESOLVED) together with
the already-built /GL objects of its callees, and diffs the function's code in that DLL against the original with
quick_diff's normalizer. About a minute per run; QD_OUT picks the output folder as for quick_diff.

Callees are found automatically and transitively: every `X_Func::name` the file (or one of its callees) calls
whose `.../X/name.cpp` is both in the build list and in cmake/compiler-flags-gl.txt (and so has a /GL object in
the build directory). Without the callee's own callees LTCG has to assume a global may change across the call
(updateGateDrawBridgeOpenCloseLogic read 0.91 with only its direct callee, 1.00 with the chain). Extra
CALLEE.cpp arguments are added to that set. The callee's MACRO_FUNCTION_RESOLVER must be enabled (enable_local_functions.py),
otherwise the call goes through the original binary and LTCG sees nothing. Run a full build first so the callee
objects exist, and do not run this while a build is running.
"""
import difflib
import os
import re
import struct
import subprocess
import sys

args = [a for a in sys.argv[1:] if not a.startswith('-')]
quiet = '-q' in sys.argv
keep = '-s' in sys.argv
if not args:
    sys.exit(__doc__)
target = os.path.abspath(args[0])
extra = [os.path.abspath(a) for a in args[1:]]
sys.argv = [sys.argv[0]] + (['-s'] if keep else [])
import quick_diff as q  # noqa: E402  (parses sys.argv on import)

ROOT = q.ROOT
out = q.out


def rel(p):
    return os.path.relpath(p, ROOT).replace(chr(92), '/')


def obj_of(src):
    return ROOT + '/build-RelWithDebInfo/CMakeFiles/OpenSHC.dll.dir/' + rel(src) + '.obj'


gl = set(l.strip() for l in open(ROOT + '/cmake/compiler-flags-gl.txt') if l.strip())
build_list = [l.strip() for l in open(ROOT + '/cmake/openshc-sources.txt.local') if l.strip()]
src = open(target, encoding='utf-8').read()
va = int(re.search(r'FUNCTION: STRONGHOLDCRUSADER (0x[0-9A-Fa-f]+)', src).group(1), 16)
cls, name = re.search(r'FUNCTION: STRONGHOLDCRUSADER[^\n]*\n[^\n(]*?(\w+)::(\w+)\(', src).groups()

def direct_callees(text):
    found = []
    for c, n in sorted(set(re.findall(r'(\w+)_Func::\s*(\w+)', text))):
        for f in build_list:
            if f.endswith('/%s/%s.cpp' % (c, n)) and f in gl and os.path.exists(obj_of(ROOT + '/' + f)):
                found.append(ROOT + '/' + f)
    return found


# transitively: LTCG only knows a callee leaves a register or a global alone if it also sees what that callee calls
callees = []
todo = direct_callees(src) + extra
while todo:
    c = todo.pop(0)
    if c in callees or os.path.abspath(c) == target:
        continue
    callees.append(c)
    todo += direct_callees(open(c, encoding='utf-8').read())
objs = [obj_of(c) for c in callees if os.path.abspath(c) != target]

# the mangled name comes from a plain /FA compile of the same file
if q.ours(target, cls, name) is None:
    sys.exit(1)
sym = re.search(r'^(\?%s@%s@\S+) PROC' % (name, cls), open(out + '/x.asm', errors='replace').read(), re.M).group(1)

glc =[e for e in q.cands if ' /GL' in e['command']]
if not glc:
    sys.exit('no /GL compile command in compile_commands.json - is any build-list file in compiler-flags-gl.txt?')
cmd = glc[0]['command']
glo = out + '/gl.obj'
cmd = re.sub(r'/Fo\S+', lambda m: '/Fo' + glo, cmd)
cmd = re.sub(r'-c \S+$', lambda m: '-c ' + target, cmd)
r = subprocess.run(cmd, cwd=glc[0]['directory'], env=q.ENV, capture_output=True, text=True)
if r.returncode:
    print('\n'.join(l for l in r.stdout.splitlines() if 'error' in l) or r.stdout[-800:])
    sys.exit(1)

dll = out + '/gl.dll'
for p in (dll, out + '/gl.map'):
    if os.path.exists(p):
        os.remove(p)
link = [ROOT + '/MSVC1400-SP1/VC/bin/link.exe', '/nologo', '/LTCG', '/DLL', '/NOENTRY', '/FORCE:UNRESOLVED',
        '/OPT:NOREF', '/OPT:NOICF', '/INCLUDE:' + sym, '/MAP:' + out + '/gl.map', '/OUT:' + dll,
        '/PDB:' + out + '/gl.pdb', '/NODEFAULTLIB', glo] + objs
r = subprocess.run(link, cwd=out, env=q.ENV, capture_output=True, text=True)
if not os.path.exists(dll) or 'fatal' in r.stdout:
    print(r.stdout[-1500:])
    sys.exit(1)
mm = re.search(r'^\s*\S+\s+' + re.escape(sym) + r'\s+([0-9a-f]{8})', open(out + '/gl.map', errors='replace').read(),
               re.M)
fva = int(mm.group(1), 16)

a = [q.canon(x) for x in q.orig(va)]
# point quick_diff's disassembler at our DLL and reuse the same normalizer
d = open(dll, 'rb').read()
pe = struct.unpack_from('<I', d, 0x3c)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]
opt = struct.unpack_from('<H', d, pe + 20)[0]
q.d = d
q.ibase = struct.unpack_from('<I', d, pe + 24 + 28)[0]
q.secs = [struct.unpack_from('<IIII', d, pe + 24 + opt + 40 * i + 8) for i in range(nsec)]
b = [q.canon(x) for x in q.orig(fva)]
ratio = difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()
print('##### %s  GL ratio %.4f  orig %d ours %d  (callees: %s)' % (
    os.path.basename(target), ratio, len(a), len(b), ', '.join(os.path.basename(c) for c in callees) or 'none'))
if not quiet:
    for l in difflib.unified_diff(a, b, lineterm='', n=2):
        if not l.startswith(('---', '+++')):
            print(l)

"""Compile one file with `_PogoFlag` forced to 2 across `Spillcosts`, and diff the result.

`Spillcosts` (0x10b10420) chooses the ordering-key penalty on `_PogoFlag`: `key -= weight` when it
is 2, `key -= count * weight` otherwise. 2 is the PGO-optimise mode, where real profile counts
make the synthetic `count` estimate unnecessary. Our builds run with 0, so every candidate carries
the larger penalty - and every register-pressure difference found against the original this
session pointed the same way, the original enregistering more than we do. A smaller penalty is
exactly what would cause that.

Patching the flag only around `Spillcosts` isolates the allocation change: the other PGO-gated
behaviour - `FgTryTailMerge` being skipped at 1, and `PogoOptCodeMotion` running at 2 - needs
profile data that does not exist here, and would crash or mislead.

usage: pogo_probe.py FILE.cpp [--value N]
"""

import os
import re
import subprocess
import sys

ROOT = r'C:\Users\Gynt\Projects\sourcehold\rea\OpenSHC-2'
sys.path.insert(0, os.path.join(ROOT, 'tools', 'reimplementation-helper', 'batch'))
import common   # noqa: E402

CDB = r"C:\Program Files (x86)\Windows Kits\10\Debuggers\x86\cdb.exe"
SPILLCOSTS = 0x10b10420
POGOFLAG = 0x10d0ffdc
BS = chr(92)


def compile_once(src, out, patch_to=None):
    """Compile `src` with /FA into `out`; if `patch_to` is set, force _PogoFlag across Spillcosts."""
    out.mkdir(parents=True, exist_ok=True)
    import json
    cc = json.loads(common.read_text(common.BUILD_DIR / 'compile_commands.json'))
    base = [e for e in cc if 'OpenSHC.dll.dir' in e['command']
            and '/src/OpenSHC/' in e['file'].replace(BS, '/')][0]
    o = str(out).replace(BS, '/')
    cmd = re.sub(r'/Fo\S+', lambda _m: '/Fo%s/p.obj /FA /Fa%s/p.asm' % (o, o), base['command'])
    cmd = re.sub(r'-c \S+$', lambda _m: '-c ' + os.path.abspath(src), cmd)
    env = common.build_env()
    env['PATH'] = str(common.ROOT / 'MSVC1400-SP1' / 'Common7' / 'IDE') + os.pathsep + env['PATH']
    if patch_to is None:
        r = subprocess.run(cmd, cwd=base['directory'], env=env, capture_output=True, text=True)
        return r.returncode, r.stdout
    # Spillcosts ends at 0x10b11559; break on entry to set the flag and on the ret to restore it,
    # so nothing outside this one pass sees a value our build was not configured for
    lines = [
        'sxe ld:c2', 'g',
        'bp0 %#x "ed %#x %d; gc"' % (SPILLCOSTS, POGOFLAG, patch_to),
        # 0x10b1153f is Spillcosts' single `ret 0xc`; the first attempt used the last byte of
        # its body, which is not an instruction boundary, so the restore never fired and the
        # flag stayed 2 into the profile-dependent passes - the compile then died on a null
        # dereference in FgFindDominatorsGraph. The phase-entry restore is a second net.
        'bp1 %#x "ed %#x 0; gc"' % (0x10b1153f, POGOFLAG),
        'bp2 %#x "ed %#x 0; gc"' % (0x10c07400, POGOFLAG),
        'g', 'q', '',
    ]
    script = out / 'pogo.cdb'
    common.write_text(script, '\r\n'.join(lines) + '\r\n')
    full = '"%s" -cf "%s" %s' % (CDB, script, cmd)
    r = subprocess.run(full, cwd=base['directory'], env=env, capture_output=True, text=True,
                       timeout=3600)
    common.write_text(out / 'pogo.log', r.stdout)
    return 0, r.stdout


def body(listing_path, src):
    text = common.read_text(src)
    m = re.search(r'FUNCTION: STRONGHOLDCRUSADER[^\n]*\n[^\n(]*?(\w+)::(\w+)\(', text)
    cls, name = m.groups()
    txt = common.read_text(listing_path)
    b = re.search(r'^(\?%s@%s@\S+) PROC.*?\n(.*?)^\1 ENDP'
                  % (re.escape(name), re.escape(cls)), txt, re.S | re.M)
    if not b:
        return None
    out = []
    for line in b.group(2).splitlines():
        line = line.split(';')[0].strip()
        if not line or line.endswith(':') or re.match(r'^\w+\$\w* = ', line):
            continue
        if line.startswith(('npad', '$', 'DD', 'DB', 'DW', '_')):
            continue
        out.append(re.sub(r'\s+', ' ', line))
    return out


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    src = sys.argv[1]
    val = 2
    for i, a in enumerate(sys.argv):
        if a == '--value' and i + 1 < len(sys.argv):
            val = int(sys.argv[i + 1])
    os.chdir(ROOT)
    plain = (common.ROOT / common.TMP / 'pogo_plain').resolve()
    patched = (common.ROOT / common.TMP / 'pogo_patched').resolve()

    rc, log = compile_once(src, plain, None)
    if rc:
        errs = [l for l in log.splitlines() if 'error' in l]
        sys.exit('baseline compile failed: %s' % (errs[:2] or log[-300:]))
    a = body(plain / 'p.asm', src)
    compile_once(src, patched, val)
    b = body(patched / 'p.asm', src)
    if a is None or b is None:
        sys.exit('could not extract the function from one of the listings')
    print('baseline  %d instructions' % len(a))
    print('_PogoFlag=%d  %d instructions' % (val, len(b)))
    if a == b:
        print('')
        print('IDENTICAL - forcing _PogoFlag=%d across Spillcosts changed nothing here.' % val)
        return
    import difflib
    print('')
    print('they DIFFER; unified diff (- baseline, + patched):')
    for line in difflib.unified_diff(a, b, lineterm='', n=2):
        if not line.startswith(('---', '+++')):
            print('  ' + line)


if __name__ == '__main__':
    main()

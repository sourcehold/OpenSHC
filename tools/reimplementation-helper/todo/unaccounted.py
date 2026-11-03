import os, re, subprocess
from collections import defaultdict

# data files are read from and written to the current working directory (run from the repo root)
SCRATCH = os.getcwd()
expected = set(open(os.path.join(SCRATCH, 'expected_cpp.txt'), encoding='utf-8').read().split())
exp_lower = set(p.lower() for p in expected)

ALLOW = set(
    p.lower()
    for p in [
        'src/OpenSHC/IO/LowLevelMemory/fillMemory.cpp',
        'src/OpenSHC/IO/ResourceManager/mapNames.cpp',
        'src/OpenSHC/IO/ResourceManager/paths.cpp',
        'src/OpenSHC/OS/OS.cpp',
        'src/OpenSHC/Text/TextEditorState/helpToken.cpp',
    ]
)


def run(args):
    p = subprocess.run(args, capture_output=True, text=True, errors='replace')
    return p.returncode, p.stdout


rc, out = run(['git', 'branch', '-r', '--format=%(refname:short)'])
branches = [b.strip() for b in out.splitlines() if '/reimpl/' in b and b.strip()]

unacc = defaultdict(list)  # path -> branches
casediff = defaultdict(list)
for b in branches + ['HEAD']:
    rc, out = run(['git', 'ls-tree', '-r', '--name-only', b, '--', 'src/OpenSHC'])
    for p in out.splitlines():
        p = p.strip()
        if not p.endswith('.cpp'):
            continue
        if p in expected:
            continue
        lp = p.lower()
        if lp in ALLOW:
            continue
        if lp in exp_lower:
            casediff[p].append(b)
        else:
            unacc[p].append(b)

print('paths differing only in case from an expected path:', len(casediff))
for p, bs in sorted(casediff.items()):
    print('   %-70s %d branches' % (p, len(bs)))

print()
print('cpp paths with NO counterpart in main headers (even case-insensitively):', len(unacc))
for p, bs in sorted(unacc.items()):
    print('   %-72s %2d br  e.g. %s' % (p, len(bs), bs[0]))

with open(os.path.join(SCRATCH, 'unaccounted_cpp.tsv'), 'w', encoding='utf-8', newline='\n') as f:
    f.write('kind\tpath\tbranch_count\tbranches\n')
    for p, bs in sorted(casediff.items()):
        f.write('CASE\t%s\t%d\t%s\n' % (p, len(bs), ','.join(sorted(bs))))
    for p, bs in sorted(unacc.items()):
        f.write('UNACCOUNTED\t%s\t%d\t%s\n' % (p, len(bs), ','.join(sorted(bs))))

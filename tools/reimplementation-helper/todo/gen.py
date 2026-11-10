import os, re
from collections import Counter

# data files are read from and written to the current working directory (run from the repo root)
SCRATCH = os.getcwd()
root = 'src/OpenSHC'
pat = re.compile(r'MACRO_FUNCTION_RESOLVER\s*\(')
rows = []
fails = []
for dirpath, dirs, files in os.walk(root):
    for fn in files:
        if not fn.endswith('.func.hpp'):
            continue
        p = os.path.join(dirpath, fn).replace(os.sep, '/')
        base = p[: -len('.func.hpp')]
        txt = open(p, encoding='utf-8', errors='replace').read()
        for m in pat.finditer(txt):
            i = m.end() - 1
            depth = 0
            while i < len(txt):
                if txt[i] == '(':
                    depth += 1
                elif txt[i] == ')':
                    depth -= 1
                    if depth == 0:
                        break
                i += 1
            tail = txt[i + 1 : i + 400]
            nm = re.match(r'\s*([A-Za-z_~][A-Za-z0-9_]*)\s*;', tail)
            if not nm:
                fails.append((p, tail[:60]))
                continue
            rows.append((base + '/' + nm.group(1) + '.cpp', p, nm.group(1)))

print('resolvers:', len(rows), 'parse fails:', len(fails))
for f in fails[:10]:
    print('  FAIL', f[0], repr(f[1]))

c = Counter(r[0] for r in rows)
dups = {k: v for k, v in c.items() if v > 1}
print('duplicate target paths (overloads):', len(dups))
for k, v in list(dups.items())[:20]:
    print('  ', k, v)

paths = sorted(c)
with open(os.path.join(SCRATCH, 'expected_cpp.txt'), 'w', encoding='utf-8', newline='\n') as f:
    f.write('\n'.join(paths) + '\n')
print('unique expected cpp:', len(paths))
print('exist in working tree:', sum(1 for p in paths if os.path.exists(p)))

# cpp files on disk that are not in the expected list
on_disk = []
for dirpath, dirs, files in os.walk(root):
    for fn in files:
        if fn.endswith('.cpp'):
            on_disk.append(os.path.join(dirpath, fn).replace(os.sep, '/'))
extra = sorted(set(on_disk) - set(paths))
print('cpp on disk NOT in expected list:', len(extra))
for e in extra[:30]:
    print('  ', e)

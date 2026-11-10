import os, re, subprocess

# data files are read from and written to the current working directory (run from the repo root)
SCRATCH = os.getcwd()
# address -> expected cpp, rebuilt from main headers
res_pat = re.compile(r'MACRO_FUNCTION_RESOLVER\s*\(')
addr_pat = re.compile(r'Address::SHC_[0-9A-Fa-f]+_0x([0-9A-Fa-f]{8})')
by_addr = {}
for dirpath, dirs, files in os.walk('src/OpenSHC'):
    for fn in files:
        if not fn.endswith('.func.hpp'):
            continue
        p = os.path.join(dirpath, fn).replace(os.sep, '/')
        base = p[: -len('.func.hpp')]
        txt = open(p, encoding='utf-8', errors='replace').read()
        for m in res_pat.finditer(txt):
            i, depth = m.end() - 1, 0
            while i < len(txt):
                if txt[i] == '(':
                    depth += 1
                elif txt[i] == ')':
                    depth -= 1
                    if depth == 0:
                        break
                i += 1
            nm = re.match(r'\s*([A-Za-z_~][A-Za-z0-9_]*)\s*;', txt[i + 1 : i + 400])
            a = addr_pat.search(txt[m.end() - 1 : i + 1])
            if a and nm:
                by_addr[a.group(1).upper()] = base + '/' + nm.group(1) + '.cpp'

fn_pat = re.compile(r'//\s*FUNCTION:\s*\S+\s+0x([0-9A-Fa-f]{8})')
rows = []
for line in open(os.path.join(SCRATCH, 'unaccounted_cpp.tsv'), encoding='utf-8'):
    parts = line.rstrip('\n').split('\t')
    if parts[0] != 'UNACCOUNTED':
        continue
    path, branches = parts[1], parts[3].split(',')
    b = branches[0]
    p = subprocess.run(['git', 'show', '%s:%s' % (b, path)], capture_output=True, text=True, errors='replace')
    addrs = sorted(set(m.group(1).upper() for m in fn_pat.finditer(p.stdout)))
    mapped = [(a, by_addr.get(a, 'NO RESOLVER IN MAIN')) for a in addrs]
    rows.append((path, b, mapped))

renames, truly_new = [], []
for path, b, mapped in rows:
    if mapped and all(t != 'NO RESOLVER IN MAIN' for _, t in mapped):
        renames.append((path, b, mapped))
    else:
        truly_new.append((path, b, mapped))

print('branch cpp that map onto a main resolver under a DIFFERENT name:', len(renames))
for path, b, mapped in renames:
    for a, t in mapped:
        print('   0x%s  %s' % (a, path))
        print('              -> main expects %s' % t)

print()
print('branch cpp with an address main has NO resolver for (or no marker):', len(truly_new))
for path, b, mapped in truly_new:
    print('   %s  [%s]  %s' % (path, b, mapped if mapped else 'no // FUNCTION: marker'))

with open(os.path.join(SCRATCH, 'rename_map.tsv'), 'w', encoding='utf-8', newline='\n') as f:
    f.write('address\tbranch_path\tmain_expected_path\tsample_branch\n')
    for path, b, mapped in renames + truly_new:
        for a, t in mapped or [('', '')]:
            f.write('0x%s\t%s\t%s\t%s\n' % (a, path, t, b))

import os, re, subprocess, json
from collections import Counter

# data files are read from and written to the current working directory (run from the repo root)
SCRATCH = os.getcwd()
ROOT = 'src/OpenSHC'


def run(args):
    p = subprocess.run(args, capture_output=True, text=True, errors='replace')
    return p.returncode, p.stdout, p.stderr


# --- 1. main's header inventory: address -> expected cpp path -------------
res_pat = re.compile(r'MACRO_FUNCTION_RESOLVER\s*\(')
addr_pat = re.compile(r'Address::(SHC_[0-9A-Fa-f]+_0x([0-9A-Fa-f]{8}))')

by_addr = {}
noaddr = []
for dirpath, dirs, files in os.walk(ROOT):
    for fn in files:
        if not fn.endswith('.func.hpp'):
            continue
        p = os.path.join(dirpath, fn).replace(os.sep, '/')
        base = p[: -len('.func.hpp')]
        txt = open(p, encoding='utf-8', errors='replace').read()
        for m in res_pat.finditer(txt):
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
            args = txt[m.end() - 1 : i + 1]
            nm = re.match(r'\s*([A-Za-z_~][A-Za-z0-9_]*)\s*;', txt[i + 1 : i + 400])
            name = nm.group(1) if nm else '?'
            cpp = base + '/' + name + '.cpp'
            a = addr_pat.search(args)
            if not a:
                noaddr.append((cpp, args[:120]))
                continue
            key = a.group(2).upper()
            by_addr.setdefault(key, []).append((a.group(1), cpp))

print('resolvers with an address:', sum(len(v) for v in by_addr.values()))
print('distinct addresses:', len(by_addr))
print('resolvers WITHOUT a parseable address:', len(noaddr))
for c, a in noaddr[:10]:
    print('   ', c, '|', a.replace('\n', ' ')[:100])
multi = {k: v for k, v in by_addr.items() if len(v) > 1}
print('addresses mapped by >1 resolver:', len(multi))
for k, v in list(multi.items())[:10]:
    print('   0x' + k, [x[1] for x in v])


# --- 2. per-branch coverage from // FUNCTION: markers ---------------------
fn_pat = re.compile(r'//\s*FUNCTION:\s*\S+\s+0x([0-9A-Fa-f]{8})')
rc, out, _ = run(['git', 'branch', '-r', '--format=%(refname:short)'])
branches = [b.strip() for b in out.splitlines() if '/reimpl/' in b and b.strip()]
print()
print('reimpl branches:', len(branches))

branch_cov = {}
for b in branches:
    rc, out, err = run(['git', 'grep', '-h', '-E', '// FUNCTION:', b, '--', 'src/OpenSHC/*.cpp'])
    if rc not in (0, 1):
        print('  !! git grep failed on', b, err.strip()[:160])
        continue
    addrs = set(m.group(1).upper() for m in fn_pat.finditer(out))
    branch_cov[b] = addrs

# main's own coverage
rc, out, _ = run(['git', 'grep', '-h', '-E', '// FUNCTION:', 'HEAD', '--', 'src/OpenSHC/*.cpp'])
main_cov = set(m.group(1).upper() for m in fn_pat.finditer(out))
print('addresses implemented on main:', len(main_cov))

all_addrs = set(by_addr)
union = set(main_cov)
for a in branch_cov.values():
    union |= a
union &= all_addrs  # ignore markers for things main's headers do not declare

todo = sorted(all_addrs - union)
print('covered on main or any reimpl branch:', len(union))
print('TODO addresses:', len(todo))

# unknown markers: implemented somewhere but no matching address in main headers
unknown = sorted((set(main_cov) | set().union(*branch_cov.values()) if branch_cov else set(main_cov)) - all_addrs)
print('implemented addresses with NO resolver in main headers:', len(unknown))
for u in unknown[:40]:
    who = [b for b, s in branch_cov.items() if u in s]
    print('   0x' + u, ('main' if u in main_cov else '') , who[:3])

# --- 3. outputs ----------------------------------------------------------
with open(os.path.join(SCRATCH, 'todo_cpp.txt'), 'w', encoding='utf-8', newline='\n') as f:
    for a in todo:
        for sid, cpp in by_addr[a]:
            f.write(cpp + '\n')

with open(os.path.join(SCRATCH, 'todo_detail.tsv'), 'w', encoding='utf-8', newline='\n') as f:
    f.write('address\tshc_id\texpected_cpp\n')
    for a in todo:
        for sid, cpp in by_addr[a]:
            f.write('0x%s\t%s\t%s\n' % (a, sid, cpp))

rows = []
for b in sorted(branch_cov, key=lambda x: -len(branch_cov[x] - main_cov)):
    new = branch_cov[b] - main_cov
    rows.append((b, len(branch_cov[b]), len(new), len(new & all_addrs)))
with open(os.path.join(SCRATCH, 'branch_coverage.tsv'), 'w', encoding='utf-8', newline='\n') as f:
    f.write('branch\timplemented\tnot_on_main\tnot_on_main_and_in_headers\n')
    for r in rows:
        f.write('%s\t%d\t%d\t%d\n' % r)
print()
print('top branches by addresses not yet on main:')
for r in rows[:20]:
    print('   %-55s impl=%-5d new=%-5d new_in_headers=%d' % r)

ns = Counter(p.split('/')[2] for a in todo for _, p in by_addr[a])
print()
print('TODO by top-level namespace:', dict(ns.most_common()))

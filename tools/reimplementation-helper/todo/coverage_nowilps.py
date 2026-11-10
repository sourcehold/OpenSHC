import os, re, subprocess
from collections import Counter

# data files are read from and written to the current working directory (run from the repo root)
SCRATCH = os.getcwd()
EXCLUDE = re.compile(r'wilps', re.I)


def run(args):
    p = subprocess.run(args, capture_output=True, text=True, errors='replace')
    return p.returncode, p.stdout


# address -> (shc id, expected cpp) from main's headers
res_pat = re.compile(r'MACRO_FUNCTION_RESOLVER\s*\(')
addr_pat = re.compile(r'Address::(SHC_[0-9A-Fa-f]+_0x([0-9A-Fa-f]{8}))')
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
                by_addr[a.group(2).upper()] = (a.group(1), base + '/' + nm.group(1) + '.cpp')

fn_pat = re.compile(r'//\s*FUNCTION:\s*\S+\s+0x([0-9A-Fa-f]{8})')


def cov(ref):
    rc, out = run(['git', 'grep', '-h', '-E', '// FUNCTION:', ref, '--', 'src/OpenSHC/*.cpp'])
    return set(m.group(1).upper() for m in fn_pat.finditer(out))


rc, out = run(['git', 'branch', '-r', '--format=%(refname:short)'])
allb = [b.strip() for b in out.splitlines() if '/reimpl/' in b and b.strip()]
kept = [b for b in allb if not EXCLUDE.search(b)]
dropped = [b for b in allb if EXCLUDE.search(b)]

main_cov = cov('HEAD')
branch_cov = {b: cov(b) for b in allb}

all_addrs = set(by_addr)
union_kept = set(main_cov)
for b in kept:
    union_kept |= branch_cov[b]
union_kept &= all_addrs

union_all = set(main_cov)
for b in allb:
    union_all |= branch_cov[b]
union_all &= all_addrs

todo = sorted(all_addrs - union_kept)
print('reimpl branches: %d total, %d kept, %d excluded' % (len(allb), len(kept), len(dropped)))
for b in dropped:
    only = branch_cov[b] & all_addrs - (set(main_cov) | set().union(*[branch_cov[x] for x in allb if x != b]))
    print('   excluded %-45s impl=%-5d uniquely covers %d' % (b, len(branch_cov[b]), len(only)))
print()
print('TODO with wilps branches counted:    %d' % len(all_addrs - union_all))
print('TODO with wilps branches excluded:   %d' % len(todo))

OS_CRT = 'src/OpenSHC/OS/'
out_path = os.path.join(SCRATCH, 'todo_detail_no_wilps.tsv')
with open(out_path, 'w', encoding='utf-8', newline='\n') as f:
    f.write('address\tshc_id\texpected_cpp\tnamespace\tis_os_crt_thunk\n')
    for a in todo:
        sid, cpp = by_addr[a]
        f.write(
            '0x%s\t%s\t%s\t%s\t%s\n'
            % (a, sid, cpp, cpp.split('/')[2], 'yes' if cpp.startswith(OS_CRT) and '/' not in cpp[len(OS_CRT):] else 'no')
        )
print('wrote', out_path, '(%d rows)' % len(todo))

ns = Counter(by_addr[a][1].split('/')[2] for a in todo)
print('TODO by namespace:', dict(ns.most_common()))

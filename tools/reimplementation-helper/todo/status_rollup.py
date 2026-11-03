"""Roll up the per-address status files of main and every reimpl/ branch.

Reads status/addresses-SHC-*.txt from HEAD and from each remote reimpl/ branch
(branch contents are taken as truth, nothing is re-measured) and writes one TSV
row per SHC id saying whether it is at 100% somewhere or still needs work.

Run from the repo root:
    python -I tools/reimplementation-helper/todo/status_rollup.py

Output: status_rollup.tsv in the current working directory.

Set REIMPL_FILTER to a regex to widen or narrow which remote-tracking branches
are scanned (default '/reimpl/'). Note for Git Bash on Windows: a value that
starts with '/' is rewritten into a Windows path by MSYS, which silently turns
the regex into one that matches nothing -- prefix the command with
MSYS_NO_PATHCONV=1, or write the pattern without a leading slash.
"""

import os, re, subprocess
from collections import Counter

# data files are read from and written to the current working directory (run from the repo root)
SCRATCH = os.getcwd()
ROOT = 'src/OpenSHC'
STATUS_GLOB = re.compile(r'^status/addresses-SHC-[0-9A-Fa-f]+\.txt$')
# one entry per line: SHC_<hash>_0x<addr> | <pct>% | <status text>
ENTRY = re.compile(r'^\s*(SHC_[0-9A-Fa-f]+_0x([0-9A-Fa-f]+))\s*\|\s*([0-9.]+)%\s*\|\s*(.*?)\s*$')


def run(args):
    p = subprocess.run(args, capture_output=True, text=True, errors='replace')
    return p.returncode, p.stdout


def status_files(ref):
    rc, out = run(['git', 'ls-tree', '-r', '--name-only', ref, '--', 'status'])
    return [p.strip() for p in out.splitlines() if STATUS_GLOB.match(p.strip())]


def parse(ref, path):
    """-> {shc_id: (pct, status_text)} for one status file at one ref."""
    rc, out = run(['git', 'show', '%s:%s' % (ref, path)])
    if rc != 0:
        return {}
    rows = {}
    for line in out.splitlines():
        m = ENTRY.match(line)
        if not m:
            continue
        rows[m.group(1)] = (float(m.group(3)), m.group(4))
    return rows


# --- main's header inventory: shc id -> expected cpp path -----------------
res_pat = re.compile(r'MACRO_FUNCTION_RESOLVER\s*\(')
addr_pat = re.compile(r'Address::(SHC_[0-9A-Fa-f]+_0x([0-9A-Fa-f]{8}))')
cpp_of = {}
for dirpath, dirs, files in os.walk(ROOT):
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
                cpp_of[a.group(1)] = base + '/' + nm.group(1) + '.cpp'
print('resolvers in main headers:', len(cpp_of))

# --- collect every ref's status rows --------------------------------------
# which remote-tracking branches to include; override in CI with REIMPL_FILTER
BRANCH_FILTER = re.compile(os.environ.get('REIMPL_FILTER', '/reimpl/'))
rc, out = run(['git', 'branch', '-r', '--format=%(refname:short)'])
refs = ['HEAD'] + sorted(
    b.strip() for b in out.splitlines() if b.strip() and BRANCH_FILTER.search(b) and '->' not in b
)

per_ref = {}
missing = []
for ref in refs:
    paths = status_files(ref)
    if not paths:
        missing.append(ref)
        continue
    rows = {}
    for p in paths:
        rows.update(parse(ref, p))
    per_ref[ref] = rows
print('refs scanned: %d (%d with a status file)' % (len(refs), len(per_ref)))
if missing:
    print('refs with NO status file:', len(missing))
    for r in missing[:10]:
        print('   ', r)

# --- roll up --------------------------------------------------------------
best = {}  # shc id -> (pct, status, ref)
at100 = Counter()
for ref in per_ref:
    for sid, (pct, st) in per_ref[ref].items():
        if pct >= 100.0:
            at100[sid] += 1
        cur = best.get(sid)
        # keep the highest pct; on a tie prefer main so its remark text wins
        if cur is None or pct > cur[0] or (pct == cur[0] and ref == 'HEAD'):
            best[sid] = (pct, st, 'main' if ref == 'HEAD' else ref)

universe = set(cpp_of) | set(sid for sid, (pct, st, r) in best.items() if pct > 0.0)
print('ids in scope: %d (resolver in headers, or >0%% somewhere)' % len(universe))

out_path = os.path.join(SCRATCH, 'status_rollup.tsv')
done = needs = 0
with open(out_path, 'w', encoding='utf-8', newline='\n') as f:
    f.write(
        'shc_id\taddress\tdone\tbest_pct\tbest_status\tbest_source\trefs_at_100\thas_resolver\texpected_cpp\n'
    )
    for sid in sorted(universe, key=lambda s: s.split('_0x')[-1]):
        pct, st, ref = best.get(sid, (0.0, 'Pending', ''))
        is_done = pct >= 100.0
        done += is_done
        needs += not is_done
        f.write(
            '%s\t0x%s\t%s\t%.1f\t%s\t%s\t%d\t%s\t%s\n'
            % (
                sid,
                sid.split('_0x')[-1],
                'yes' if is_done else 'no',
                pct,
                st,
                ref,
                at100.get(sid, 0),
                'yes' if sid in cpp_of else 'no',
                cpp_of.get(sid, ''),
            )
        )
print('wrote %s (%d rows)' % (out_path, done + needs))
print('  at 100%% somewhere: %d' % done)
print('  still need work:   %d' % needs)

buckets = Counter()
for sid in universe:
    pct = best.get(sid, (0.0,))[0]
    if pct >= 100.0:
        continue
    buckets['0% (not started)' if pct == 0.0 else '%d-%d%%' % (int(pct // 10) * 10, int(pct // 10) * 10 + 9)] += 1
print('  breakdown of the unfinished:', dict(sorted(buckets.items())))

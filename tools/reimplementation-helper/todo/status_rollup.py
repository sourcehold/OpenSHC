"""Roll up the per-address status files of main and every fork branch.

Reads status/addresses-SHC-*.txt from HEAD and from every remote-tracking branch
(branch contents are taken as truth, nothing is re-measured) and writes one TSV
row per SHC id saying whether it is at 100% somewhere or still needs work.

Every branch, not only the reimpl/ ones: finished work turns up on branches
named for whatever produced it (ci/, cishard/, civar/, buildings-update-...),
and two such branches on one fork alone held 300+ entries better than the rollup
knew about while only reimpl/ was scanned.

Run from the repo root:
    python -I tools/reimplementation-helper/todo/status_rollup.py

Only branches that are present as remote-tracking refs can be read, so a plain
clone sees nothing but its own. Pass --fetch-forks (or set REIMPL_FETCH_FORKS=1)
to add every fork of the root repository as a remote first and shallow-fetch all
of its branches, which is what fetch_fork_branches.sh does:

    python -I tools/reimplementation-helper/todo/status_rollup.py --fetch-forks

That needs gh, authenticated (GH_TOKEN). Only branch tips are fetched, and
nothing from a fetched branch is ever executed -- one status file per ref is
read. The repository is taken from --repo, else REIMPL_REPO, else the origin
remote, else sourcehold/OpenSHC. Without the flag the fetch is skipped and only
what is already fetched is scanned, so the CI workflow keeps working unchanged.

Output: status_rollup.tsv in the current working directory.

Set REIMPL_FILTER to a regex to narrow which remote-tracking branches are
scanned (default: all of them). Note for Git Bash on Windows: a value that
starts with '/' is rewritten into a Windows path by MSYS, which silently turns
the regex into one that matches nothing -- prefix the command with
MSYS_NO_PATHCONV=1, or write the pattern without a leading slash.

The helpers here are also imported by status_regression.py, so keep the module
importable: everything that runs belongs in main().
"""

import argparse, os, re, subprocess
from collections import Counter

ROOT = 'src/OpenSHC'
#: the project's own repository; forks are enumerated from its root
DEFAULT_REPO = 'sourcehold/OpenSHC'
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


def rows_at(ref):
    """-> {shc_id: (pct, status_text)} merged over every status file at one ref."""
    rows = {}
    for p in status_files(ref):
        rows.update(parse(ref, p))
    return rows


RESOLVER = re.compile(r'MACRO_FUNCTION_RESOLVER\s*\(')
RESOLVER_ADDR = re.compile(r'Address::(SHC_[0-9A-Fa-f]+_0x([0-9A-Fa-f]{8}))')


def parse_resolvers(txt, path):
    """-> {shc id: expected cpp path} for the resolvers in one .func.hpp text.

    `path` is the header's repo-relative path; the cpp is expected in the folder
    named after it. Kept separate from the walk below so status_regression.py
    can run it on a header read out of a ref instead of the working tree.
    """
    base = path[: -len('.func.hpp')]
    cpp_of = {}
    for m in RESOLVER.finditer(txt):
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
        a = RESOLVER_ADDR.search(txt[m.end() - 1 : i + 1])
        if a and nm:
            cpp_of[a.group(1)] = base + '/' + nm.group(1) + '.cpp'
    return cpp_of


def header_cpp_map():
    """-> {shc id: expected cpp path} from the resolvers in the working tree's headers."""
    cpp_of = {}
    for dirpath, dirs, files in os.walk(ROOT):
        for fn in files:
            if not fn.endswith('.func.hpp'):
                continue
            p = os.path.join(dirpath, fn).replace(os.sep, '/')
            cpp_of.update(parse_resolvers(open(p, encoding='utf-8', errors='replace').read(), p))
    return cpp_of


REPO_NAME = re.compile(r'^[A-Za-z0-9._-]+/[A-Za-z0-9._-]+$')


def origin_repo():
    """-> 'owner/name' of the origin remote, or '' if it is not a GitHub url."""
    rc, out = run(['git', 'remote', 'get-url', 'origin'])
    url = out.strip()
    if url.endswith('.git'):
        url = url[:-4]
    m = re.search(r'github\.com[:/]+([A-Za-z0-9._-]+/[A-Za-z0-9._-]+)/?$', url)
    return m.group(1) if m else ''


def fork_repos(repo_full_name):
    """-> [root repo, every fork of it]; the root is the repo's parent, if any."""
    rc, out = run(['gh', 'repo', 'view', repo_full_name, '--json', 'parent,nameWithOwner',
                   '--jq', 'if .parent then .parent.owner.login + "/" + .parent.name '
                           'else .nameWithOwner end'])
    if rc != 0 or not out.strip():
        raise RuntimeError('gh repo view %s failed (is gh installed and authenticated?)'
                           % repo_full_name)
    root = out.strip()
    rc, out = run(['gh', 'api', 'repos/%s/forks' % root, '--paginate',
                   '--jq', '.[].full_name'])
    if rc != 0:
        raise RuntimeError('gh api repos/%s/forks failed' % root)
    repos = {root} | {ln.strip() for ln in out.splitlines() if ln.strip()}
    # ignore anything that is not a plain owner/name, so that a surprising API
    # response cannot turn into command arguments or a path
    return root, sorted(r for r in repos if REPO_NAME.match(r))


def fetch_fork_branches(repo_full_name=None):
    """Add every fork as a remote and shallow-fetch all of its branches.

    The Python counterpart of fetch_fork_branches.sh, so that a local run covers
    the same branches CI does. Only branch tips are fetched.

    Every branch, not just reimpl/: finished work turns up on branches named for
    whatever produced it (ci/, cishard/, civar/, buildings-update-...), and two
    such branches on one fork alone held 300+ entries better than the rollup
    knew about while only reimpl/ was fetched.
    """
    repo_full_name = (repo_full_name or os.environ.get('REIMPL_REPO')
                      or origin_repo() or DEFAULT_REPO)
    root, repos = fork_repos(repo_full_name)
    print('root repository: %s' % root)
    print('repositories to scan: %d' % len(repos))
    fetched = 0
    for repo in repos:
        remote = repo.replace('/', '-')
        run(['git', 'remote', 'remove', remote])
        run(['git', 'remote', 'add', remote, 'https://github.com/%s' % repo])
        # an empty or unreachable fork is normal, not an error
        rc, out = run(['git', 'fetch', '--no-tags', '--depth=1', remote,
                       '+refs/heads/*:refs/remotes/%s/*' % remote])
        if rc != 0:
            print('  %s: skipped (unreachable)' % repo)
            continue
        rc, out = run(['git', 'branch', '-r', '--list', '%s/*' % remote])
        n = len([b for b in out.splitlines() if b.strip() and '->' not in b])
        if n:
            fetched += n
            print('  %s: %d branch(es)' % (repo, n))
    print('fetched branches: %d' % fetched)


def reimpl_refs(filter_re=None, exclude_shas=()):
    """-> ['HEAD', <remote-tracking branches matching the filter>] (sorted).

    Every remote-tracking branch by default: work worth finding sits on branches
    named for whatever produced it, not only on reimpl/ ones. Set REIMPL_FILTER
    to narrow it again.
    """
    if filter_re is None:
        # which remote-tracking branches to include; override with REIMPL_FILTER
        filter_re = re.compile(os.environ.get('REIMPL_FILTER', ''))
    rc, out = run(['git', 'branch', '-r', '--format=%(refname:short)'])
    refs = []
    for b in out.splitlines():
        b = b.strip()
        if not b or '->' in b or not filter_re.search(b):
            continue
        if exclude_shas:
            rc, sha = run(['git', 'rev-parse', b])
            if sha.strip() in exclude_shas:
                continue
        refs.append(b)
    return ['HEAD'] + sorted(refs)


def best_per_id(refs):
    """-> ({shc id: (pct, status, source)}, Counter of refs at 100%, refs that had a status file)."""
    best = {}
    at100 = Counter()
    seen = []
    for ref in refs:
        rows = rows_at(ref)
        if not rows:
            continue
        seen.append(ref)
        for sid, (pct, st) in rows.items():
            if pct >= 100.0:
                at100[sid] += 1
            cur = best.get(sid)
            # keep the highest pct; on a tie prefer main so its remark text wins
            if cur is None or pct > cur[0] or (pct == cur[0] and ref == 'HEAD'):
                best[sid] = (pct, st, 'main' if ref == 'HEAD' else ref)
    return best, at100, seen


def remote_repos():
    """-> {remote name: 'owner/name'} from the remotes' urls.

    The url is the only reliable source: a remote added by hand is not named
    after the repository, and an owner or a name may itself contain a dash, so
    splitting the 'owner-name' remote fetch_fork_branches creates is ambiguous.
    """
    rc, out = run(['git', 'remote', '-v'])
    repos = {}
    for line in out.splitlines():
        parts = line.split()
        if len(parts) < 2 or parts[0] in repos:
            continue
        url = parts[1][:-4] if parts[1].endswith('.git') else parts[1]
        m = re.search(r'github\.com[:/]+([A-Za-z0-9._-]+/[A-Za-z0-9._-]+)/?$', url)
        if m:
            repos[parts[0]] = m.group(1)
    return repos


def fork_of(ref, repos=None):
    """'owner-name/reimpl/foo' -> 'owner/name'; the remote name has no slash."""
    if ref == 'HEAD':
        return 'main'
    remote = ref.split('/', 1)[0]
    if repos is None:
        repos = remote_repos()
    if remote in repos:
        return repos[remote]
    owner, _, name = remote.partition('-')
    return '%s/%s' % (owner, name) if name else remote


def main(argv=None):
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--fetch-forks', action='store_true',
                    default=os.environ.get('REIMPL_FETCH_FORKS') == '1',
                    help='add every fork as a remote and shallow-fetch all of its '
                         'branches before rolling up (needs gh; REIMPL_FETCH_FORKS=1)')
    ap.add_argument('--repo', default=os.environ.get('REIMPL_REPO'),
                    help="repository to enumerate the forks of, as owner/name "
                         "(default: REIMPL_REPO, else the origin remote, else "
                         + DEFAULT_REPO + ")")
    args = ap.parse_args(argv)

    if args.fetch_forks:
        fetch_fork_branches(args.repo)

    # data files are written to the current working directory (run from the repo root)
    cpp_of = header_cpp_map()
    print('resolvers in main headers:', len(cpp_of))

    refs = reimpl_refs()
    best, at100, seen = best_per_id(refs)
    print('refs scanned: %d (%d with a status file)' % (len(refs), len(seen)))
    repos = remote_repos()
    # GitHub repository names are case-insensitive, and the same fork is often
    # reachable under two remotes, so count one entry per repository
    forks = Counter(fork_of(r, repos).lower() for r in refs)
    print('forks covered: %d' % len([f for f in forks if f != 'main']))
    for fork, n in sorted(forks.items(), key=lambda kv: (-kv[1], kv[0])):
        if fork != 'main':
            print('   %-40s %d branch(es)' % (fork, n))
    if len(forks) <= 1 and not args.fetch_forks:
        print('NOTE: no fork branches are fetched; rerun with --fetch-forks to '
              'include every fork of the repository')
    missing = [r for r in refs if r not in seen]
    if missing:
        print('refs with NO status file:', len(missing))
        for r in missing[:10]:
            print('   ', r)

    universe = set(cpp_of) | set(sid for sid, (pct, st, r) in best.items() if pct > 0.0)
    print('ids in scope: %d (resolver in headers, or >0%% somewhere)' % len(universe))

    out_path = os.path.join(os.getcwd(), 'status_rollup.tsv')
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
        buckets[
            '0% (not started)' if pct == 0.0 else '%d-%d%%' % (int(pct // 10) * 10, int(pct // 10) * 10 + 9)
        ] += 1
    print('  breakdown of the unfinished:', dict(sorted(buckets.items())))


if __name__ == '__main__':
    main()

"""Report the status entries a pull request lowers below the best known match.

The match percentages in status/addresses-SHC-*.txt are taken for granted, as
in status_rollup.py: nothing is re-measured here. For every id whose status
line the PR changes, the PR's percentage is compared against the best already
known anywhere -- the base branch plus every fork's reimpl/ branches -- and the
ones that come out lower are reported, grouped by the cpp file the resolver in
the base branch's headers points at.

Only the .cpp files the change actually edits are considered: the file list is
the diff against the MERGE BASE of PR_REF and BASE_REF, so a branch that is
merely out of date is not blamed for the older status lines it carries along.
That needs both refs fetched with enough history for `git merge-base`; a
depth-1 fetch of either one is a hard error rather than a fallback, because
without the file list an out-of-date branch reports hundreds of regressions it
did not cause.

Run from the repo root of a checkout of the BASE branch, with the PR head
fetched as data under some ref:

    PR_REF=pr/314 python -I tools/reimplementation-helper/todo/status_regression.py

Environment:
    PR_REF         ref holding the PR head (required)
    BASE_REF       ref the merge base is taken against, and the baseline for
                   "what the PR changed" (default HEAD)
    PR_HEAD_SHA    if set, any remote branch at one of these commits (whitespace
                   or comma separated) is left out of the baseline, so a fork's
                   own reimpl/ branch cannot be counted as prior art against the
                   PR that proposes it. A merge group may hold several PRs, hence
                   the list.
    REIMPL_FILTER  regex of remote-tracking branches to include (default '/reimpl/')
    REIMPL_FETCH_FORKS  '1' to add every fork as a remote and shallow-fetch its
                   reimpl/ branches first, so the baseline covers every fork
                   without a separate fetch step (needs gh, authenticated). The
                   fetch happens only after the touched-file list is settled,
                   because it grafts the commit under test as parentless.
    REIMPL_REPO    repository whose forks are enumerated, as owner/name (default:
                   the origin remote, else sourcehold/OpenSHC)
    TOUCHED_LIST   file of one changed path per line; when set it is used instead
                   of asking git, so the list can be worked out before anything
                   shallow is fetched into the repository
    OUT            markdown report path (default status_regression.md)
    FAIL_ON_REGRESSION  '1' to exit 2 when something regressed

Output: the markdown report, and a summary on stdout.
"""

import os, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from status_rollup import (rows_at, header_cpp_map, reimpl_refs, best_per_id, run,
                           parse_resolvers, fetch_fork_branches)

# status files carry one decimal, so compare with a tolerance below that
EPS = 0.05
# a comment with hundreds of rows is unreadable; the full list stays in the job log
MAX_ROWS = 50


def touched_files(base_ref, pr_ref):
    """-> (set of paths changed since the merge base, merge base sha) or (None, '').

    The merge base, not the base ref's tip: a branch that is simply behind main
    carries main's older status lines, and diffing against the tip would read
    every one of those as something this change did.

    None means the question could not be answered -- no merge base, because one
    of the refs is shallow.

    TOUCHED_LIST short-circuits all of it: a file of one path per line, worked
    out earlier by the caller. CI needs that, because fetching the fork reimpl/
    branches shallow grafts the commit under test as parentless whenever the
    pull request comes FROM one of those branches, which is the normal case --
    the history has to be read before that happens.
    """
    listed = os.environ.get('TOUCHED_LIST')
    if listed:
        with open(listed, encoding='utf-8') as f:
            paths = set(l.strip() for l in f if l.strip())
        return paths, '(from %s)' % listed

    rc, out = run(['git', 'merge-base', base_ref, pr_ref])
    mb = out.strip()
    if rc != 0 or not mb:
        return None, ''
    rc, out = run(['git', 'diff', '--name-only', '--diff-filter=d', mb, pr_ref])
    if rc != 0:
        return None, ''
    return set(p.strip() for p in out.splitlines() if p.strip()), mb


def resolvers_at(ref, paths):
    """-> {shc id: cpp path} for the .func.hpp files `paths` as they are at `ref`."""
    cpp_of = {}
    for p in paths:
        rc, txt = run(['git', 'show', '%s:%s' % (ref, p)])
        if rc == 0:
            cpp_of.update(parse_resolvers(txt, p))
    return cpp_of


def main():
    pr_ref = os.environ.get('PR_REF')
    if not pr_ref:
        print('PR_REF is not set; nothing to compare.')
        print('regressions=0')
        return 0
    base_ref = os.environ.get('BASE_REF', 'HEAD')
    out_path = os.environ.get('OUT', 'status_regression.md')
    # 'this PR' when checking a pull request, 'this merge group' from the queue
    label = os.environ.get('LABEL', 'this PR')

    pr_rows = rows_at(pr_ref)
    if not pr_rows:
        print('No status entries found at %s; nothing to compare.' % pr_ref)
        print('regressions=0')
        return 0
    base_rows = rows_at(base_ref)

    # Which .cpp files does the change actually touch? A status line can differ
    # for reasons that are not this change's doing -- most often a branch that
    # has not been updated since main improved the same function -- so an entry
    # only counts when the change also edits the file behind it.
    #
    # This is answered BEFORE any fork branch is fetched: a shallow fetch grafts
    # the commit under test as parentless whenever the PR comes from one of those
    # branches, and the merge base is then unanswerable.
    touched, mb = touched_files(base_ref, pr_ref)
    if touched is None:
        # Not something to work around: without the file list this would compare
        # every status line, and an out-of-date branch then reports hundreds of
        # regressions it did not cause. Fail visibly instead of gating on noise.
        print(
            'ERROR: no merge base between %s and %s. Both refs need real history here; a '
            'depth-1 fetch of either one produces exactly this.' % (base_ref, pr_ref),
            file=sys.stderr,
        )
        return 1

    if os.environ.get('REIMPL_FETCH_FORKS') == '1':
        fetch_fork_branches(os.environ.get('REIMPL_REPO'))

    # The PR's own branch may also be one of the fetched fork reimpl/ branches.
    exclude = set(os.environ.get('PR_HEAD_SHA', '').replace(',', ' ').split())
    refs = reimpl_refs(exclude_shas=exclude)
    best, at100, seen = best_per_id(refs)
    print('baseline refs with a status file: %d' % len(seen))

    cpp_of = header_cpp_map()

    # A resolver the change itself adds or moves is not in the base headers, so
    # re-read the .func.hpp files it touches at the PR's own ref.
    cpp_of = dict(cpp_of)
    cpp_of.update(resolvers_at(pr_ref, sorted(p for p in touched if p.endswith('.func.hpp'))))
    cpp_touched = set(p for p in touched if p.endswith('.cpp'))
    print('merge base: %s' % (mb if mb.startswith('(') else mb[:12]))
    print('files changed since the merge base: %d (%d .cpp)' % (len(touched), len(cpp_touched)))

    # Every entry behind a touched file, whatever its percentage says. What the
    # entry reads on the base branch is NOT a filter: a file left at the same
    # percentage as main, while a fork already has it higher, is exactly the
    # case this check exists for.
    changed = sorted(sid for sid, cpp in cpp_of.items() if cpp in cpp_touched)
    print('status entries behind those files: %d' % len(changed))
    unlisted = [sid for sid in changed if sid not in pr_rows]
    if unlisted:
        print('   (%d of them have no status line at %s)' % (len(unlisted), pr_ref))

    worse = []
    for sid in changed:
        # A file under the change with no status line of its own counts as 0%:
        # if it is known higher elsewhere, dropping the line is the same
        # regression as lowering the number in it.
        pr_pct, pr_st = pr_rows.get(sid, (0.0, '(no status line)'))
        known_pct, known_st, known_src = best.get(sid, (0.0, 'Pending', ''))
        if pr_pct < known_pct - EPS:
            worse.append((cpp_of.get(sid, ''), sid, pr_pct, pr_st, known_pct, known_st, known_src))
    # biggest drop first
    worse.sort(key=lambda r: (-(r[4] - r[2]), r[0], r[1]))

    lines = ['<!-- status-regression -->', '**Match regression check**', '']
    if not worse:
        lines.append(
            'No regression: none of the %d status entries behind the files %s changes is below the best match '
            "already known on `%s` or on any fork's `reimpl/` branch." % (len(changed), label, base_ref)
        )
    else:
        lines.append(
            '%d of the %d status entries behind the files %s changes are **below the best match already known** '
            "on `%s` or on a fork's `reimpl/` branch:" % (len(worse), len(changed), label, base_ref)
        )
        lines.append('')
        lines.append('| file | id | here | best known | where | known remark |')
        lines.append('| --- | --- | --- | --- | --- | --- |')
        for cpp, sid, pr_pct, pr_st, known_pct, known_st, known_src in worse[:MAX_ROWS]:
            lines.append(
                '| %s | `%s` | %.1f%% (%s) | %.1f%% | %s | %s |'
                % (
                    '`%s`' % cpp if cpp else '_(no resolver in base headers)_',
                    sid,
                    pr_pct,
                    pr_st or '-',
                    known_pct,
                    '`%s`' % known_src if known_src else '-',
                    known_st or '-',
                )
            )
        if len(worse) > MAX_ROWS:
            lines.append('')
            lines.append(
                '_... and %d more; the full list is in the workflow run log._'
                % (len(worse) - MAX_ROWS)
            )
        lines.append('')
        lines.append(
            'Percentages are read from the `status/addresses-SHC-*.txt` files as written; nothing '
            'is rebuilt here. If a figure above is stale, update the status file.'
        )
    lines.append('')
    with open(out_path, 'w', encoding='utf-8', newline='\n') as f:
        f.write('\n'.join(lines))

    print('wrote %s (%d regression(s))' % (out_path, len(worse)))
    print('regressions=%d' % len(worse))
    for row in worse:
        print('  %-70s %.1f%% < %.1f%% (%s)' % (row[0] or row[1], row[2], row[4], row[6]))
    if worse and os.environ.get('FAIL_ON_REGRESSION') == '1':
        return 2
    return 0


if __name__ == '__main__':
    sys.exit(main())

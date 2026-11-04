"""Report the status entries a pull request lowers below the best known match.

The match percentages in status/addresses-SHC-*.txt are taken for granted, as
in status_rollup.py: nothing is re-measured here. For every id whose status
line the PR changes, the PR's percentage is compared against the best already
known anywhere -- the base branch plus every fork's reimpl/ branches -- and the
ones that come out lower are reported, grouped by the cpp file the resolver in
the base branch's headers points at.

Run from the repo root of a checkout of the BASE branch, with the PR head
fetched as data under some ref:

    PR_REF=pr/314 python -I tools/reimplementation-helper/todo/status_regression.py

Environment:
    PR_REF         ref holding the PR head (required)
    BASE_REF       ref to compare against for "what the PR changed" (default HEAD)
    PR_HEAD_SHA    if set, any remote branch at one of these commits (whitespace
                   or comma separated) is left out of the baseline, so a fork's
                   own reimpl/ branch cannot be counted as prior art against the
                   PR that proposes it. A merge group may hold several PRs, hence
                   the list.
    REIMPL_FILTER  regex of remote-tracking branches to include (default '/reimpl/')
    OUT            markdown report path (default status_regression.md)
    FAIL_ON_REGRESSION  '1' to exit 2 when something regressed

Output: the markdown report, and a summary on stdout.
"""

import os, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from status_rollup import rows_at, header_cpp_map, reimpl_refs, best_per_id

# status files carry one decimal, so compare with a tolerance below that
EPS = 0.05
# a comment with hundreds of rows is unreadable; the full list stays in the job log
MAX_ROWS = 50


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

    # The PR's own branch may also be one of the fetched fork reimpl/ branches.
    exclude = set(os.environ.get('PR_HEAD_SHA', '').replace(',', ' ').split())
    refs = reimpl_refs(exclude_shas=exclude)
    best, at100, seen = best_per_id(refs)
    print('baseline refs with a status file: %d' % len(seen))

    cpp_of = header_cpp_map()

    changed = [sid for sid, (pct, st) in pr_rows.items() if base_rows.get(sid, (None,))[0] != pct]
    print('status entries changed by %s: %d' % (pr_ref, len(changed)))

    worse = []
    for sid in changed:
        pr_pct, pr_st = pr_rows[sid]
        known_pct, known_st, known_src = best.get(sid, (0.0, 'Pending', ''))
        if pr_pct < known_pct - EPS:
            worse.append((cpp_of.get(sid, ''), sid, pr_pct, pr_st, known_pct, known_st, known_src))
    # biggest drop first
    worse.sort(key=lambda r: (-(r[4] - r[2]), r[0], r[1]))

    lines = ['<!-- status-regression -->', '**Match regression check**', '']
    if not worse:
        lines.append(
            'No regression: none of the %d status entries %s changes is below the best match '
            "already known on `%s` or on any fork's `reimpl/` branch." % (len(changed), label, base_ref)
        )
    else:
        lines.append(
            '%d of the %d status entries %s changes are **below the best match already known** '
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

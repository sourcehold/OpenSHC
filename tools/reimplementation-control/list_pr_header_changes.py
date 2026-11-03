#!/usr/bin/env python3
"""List changes to .hpp files in pull requests of a GitHub repository.

Uses the `gh` CLI (must be installed and authenticated). For every matched pull
request the script reports the touched header files, their change status and the
added/removed line counts; with --patch it also prints the unified diff hunks.

Examples:
    python tools/reimplementation-control/list_pr_header_changes.py
    python tools/reimplementation-control/list_pr_header_changes.py --state all --limit 100
    python tools/reimplementation-control/list_pr_header_changes.py --pr 300 --patch
    python tools/reimplementation-control/list_pr_header_changes.py --path-filter src/OpenSHC/Globals --json
"""

import argparse
import fnmatch
import json
import subprocess
import sys


def gh_json(args):
    """Run a gh command and decode its JSON output."""
    proc = subprocess.run(
        ["gh"] + args, stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )
    if proc.returncode != 0:
        sys.stderr.write(proc.stderr.decode("utf-8", "replace"))
        raise SystemExit("gh %s failed with exit code %d" % (" ".join(args), proc.returncode))
    return json.loads(proc.stdout.decode("utf-8", "replace") or "null")


def list_pull_requests(repo, state, limit, numbers):
    if numbers:
        return [
            gh_json(
                [
                    "pr", "view", str(n), "--repo", repo,
                    "--json", "number,title,author,state,url,headRefName",
                ]
            )
            for n in numbers
        ]
    return gh_json(
        [
            "pr", "list", "--repo", repo,
            "--state", state, "--limit", str(limit),
            "--json", "number,title,author,state,url,headRefName",
        ]
    )


def pr_files(repo, number):
    """All files of a PR, paginated, via the REST API."""
    return gh_json(
        [
            "api", "--paginate",
            "repos/%s/pulls/%d/files?per_page=100" % (repo, number),
        ]
    )


def matches(filename, patterns, path_filter):
    if path_filter and path_filter.replace("\\", "/") not in filename:
        return False
    return any(fnmatch.fnmatch(filename, pattern) for pattern in patterns)


def collect(repo, prs, patterns, path_filter):
    results = []
    for pr in prs:
        files = [
            {
                "filename": f["filename"],
                "previous_filename": f.get("previous_filename"),
                "status": f["status"],
                "additions": f["additions"],
                "deletions": f["deletions"],
                "patch": f.get("patch"),
            }
            for f in pr_files(repo, pr["number"])
            if matches(f["filename"], patterns, path_filter)
        ]
        if not files:
            continue
        results.append(
            {
                "number": pr["number"],
                "title": pr["title"],
                "author": (pr.get("author") or {}).get("login"),
                "state": pr["state"],
                "url": pr["url"],
                "branch": pr.get("headRefName"),
                "additions": sum(f["additions"] for f in files),
                "deletions": sum(f["deletions"] for f in files),
                "files": files,
            }
        )
    return results


def print_report(results, show_patch):
    for pr in results:
        print(
            "PR #%-5d %s  (%s, %s)  +%d/-%d in %d header(s)"
            % (
                pr["number"], pr["title"], pr["author"], pr["state"],
                pr["additions"], pr["deletions"], len(pr["files"]),
            )
        )
        print("    %s" % pr["url"])
        for f in pr["files"]:
            name = f["filename"]
            if f["previous_filename"]:
                name = "%s <- %s" % (name, f["previous_filename"])
            print(
                "    %-8s +%-5d -%-5d %s"
                % (f["status"], f["additions"], f["deletions"], name)
            )
            if show_patch and f["patch"]:
                for line in f["patch"].splitlines():
                    print("        %s" % line)
        print("")
    total_files = sum(len(pr["files"]) for pr in results)
    print(
        "%d pull request(s) touching %d header file(s), +%d/-%d"
        % (
            len(results), total_files,
            sum(pr["additions"] for pr in results),
            sum(pr["deletions"] for pr in results),
        )
    )


def main(argv=None):
    parser = argparse.ArgumentParser(
        description="List .hpp changes in GitHub pull requests."
    )
    parser.add_argument("--repo", default="sourcehold/OpenSHC", help="owner/name of the repository")
    parser.add_argument("--state", default="open", choices=["open", "closed", "merged", "all"])
    parser.add_argument("--limit", type=int, default=50, help="maximum number of pull requests to scan")
    parser.add_argument("--pr", type=int, action="append", dest="numbers", help="inspect only this PR (repeatable)")
    parser.add_argument("--pattern", action="append", dest="patterns", help="glob of files to report (default *.hpp)")
    parser.add_argument("--path-filter", default="", help="only files whose path contains this substring")
    parser.add_argument("--patch", action="store_true", help="also print the diff hunks")
    parser.add_argument("--json", action="store_true", dest="as_json", help="emit machine-readable JSON")
    args = parser.parse_args(argv)

    patterns = args.patterns or ["*.hpp"]
    prs = list_pull_requests(args.repo, args.state, args.limit, args.numbers)
    results = collect(args.repo, prs, patterns, args.path_filter)

    if args.as_json:
        json.dump(results, sys.stdout, indent=2)
        sys.stdout.write("\n")
    else:
        print_report(results, args.patch)
    return 0


if __name__ == "__main__":
    sys.exit(main())

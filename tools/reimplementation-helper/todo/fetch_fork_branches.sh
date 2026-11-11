#!/usr/bin/env bash
# Add every fork of the root repository as a remote and shallow-fetch its
# reimpl/ branches, so that status_rollup.py sees them as ordinary
# remote-tracking branches.
#
# Only branch tips are fetched: the rollup reads one file per ref, and nothing
# from a fetched branch is ever executed.
#
# Requires: gh (authenticated via GH_TOKEN), git. Run from the repo root.
# Usage: tools/reimplementation-helper/todo/fetch_fork_branches.sh [owner/repo]
#
# The repository defaults to the project's own; pass another one to walk up from
# a fork instead.

set -euo pipefail

repo_full_name="${1:-sourcehold/OpenSHC}"

# Walk up to the root repository, then enumerate its forks.
root=$(gh repo view "$repo_full_name" --json parent,nameWithOwner \
         --jq 'if .parent then .parent.owner.login + "/" + .parent.name else .nameWithOwner end')
echo "Root repository: $root"

{
  echo "$root"
  gh api "repos/$root/forks" --paginate --jq '.[].full_name'
} | sort -u > /tmp/forks.txt
echo "Repositories to scan: $(wc -l < /tmp/forks.txt)"

while read -r repo; do
  [ -n "$repo" ] || continue
  # Ignore anything that is not a plain owner/name, so that a surprising API
  # response cannot turn into shell arguments or a path.
  if ! printf '%s' "$repo" | grep -qE '^[A-Za-z0-9._-]+/[A-Za-z0-9._-]+$'; then
    echo "  skipped (unexpected name): $repo"
    continue
  fi
  remote=${repo//\//-}
  git remote remove "$remote" 2>/dev/null || true
  git remote add "$remote" "https://github.com/$repo"
  # A fork with no reimpl/ branches is normal, not an error.
  if git fetch --no-tags --depth=1 "$remote" \
       "+refs/heads/reimpl/*:refs/remotes/$remote/reimpl/*" 2>/dev/null; then
    n=$(git branch -r --list "$remote/reimpl/*" | wc -l)
    [ "$n" -gt 0 ] && echo "  $repo: $n reimpl branch(es)"
  else
    echo "  $repo: skipped (unreachable or no reimpl/ branches)"
  fi
done < /tmp/forks.txt

echo "Total reimpl/ branches: $(git branch -r | grep -c '/reimpl/' || true)"

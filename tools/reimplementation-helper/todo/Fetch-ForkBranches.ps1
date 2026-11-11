<#
.SYNOPSIS
Add every fork of the root repository as a remote and shallow-fetch all of its
branches, so that status_rollup.py sees them as ordinary remote-tracking
branches.

.DESCRIPTION
Every branch, not just reimpl/: finished work turns up on branches named for
whatever produced it (ci/, cishard/, civar/, buildings-update-...), and two such
branches on one fork alone held 300+ entries better than the rollup knew about
while only reimpl/ was fetched.

Only branch tips are fetched: the rollup reads one file per ref, and nothing
from a fetched branch is ever executed.

Requires: gh (authenticated via GH_TOKEN), git. Run from the repo root.

The repository defaults to the project's own, sourcehold/OpenSHC; pass another
one to walk up from a fork instead.

.EXAMPLE
tools\reimplementation-helper\todo\Fetch-ForkBranches.ps1
#>
[CmdletBinding()]
param(
    [Parameter(Position = 0)]
    [string]$RepoFullName = 'sourcehold/OpenSHC'
)

$ErrorActionPreference = 'Stop'

# Walk up to the root repository, then enumerate its forks.
$root = gh repo view $RepoFullName --json parent,nameWithOwner `
    --jq 'if .parent then .parent.owner.login + "/" + .parent.name else .nameWithOwner end'
if ($LASTEXITCODE -ne 0) { throw "gh repo view failed for $RepoFullName" }
$root = $root.Trim()
Write-Host "Root repository: $root"

$forks = gh api "repos/$root/forks" --paginate --jq '.[].full_name'
if ($LASTEXITCODE -ne 0) { throw "gh api repos/$root/forks failed" }

$repos = @($root) + @($forks) |
    ForEach-Object { $_.Trim() } |
    Where-Object { $_ } |
    Sort-Object -Unique
Write-Host "Repositories to scan: $($repos.Count)"

foreach ($repo in $repos) {
    # Ignore anything that is not a plain owner/name, so that a surprising API
    # response cannot turn into command arguments or a path.
    if ($repo -notmatch '^[A-Za-z0-9._-]+/[A-Za-z0-9._-]+$') {
        Write-Host "  skipped (unexpected name): $repo"
        continue
    }
    $remote = $repo -replace '/', '-'
    git remote remove $remote 2>$null | Out-Null
    git remote add $remote "https://github.com/$repo"

    # An empty or unreachable fork is normal, not an error.
    git fetch --no-tags --depth=1 $remote "+refs/heads/*:refs/remotes/$remote/*" 2>$null | Out-Null
    if ($LASTEXITCODE -eq 0) {
        $n = @(git branch -r --list "$remote/*").Count
        if ($n -gt 0) { Write-Host "  ${repo}: $n branch(es)" }
    }
    else {
        Write-Host "  ${repo}: skipped (unreachable)"
    }
}

$total = @(git branch -r | Where-Object { $_ -notmatch '-> ' }).Count
Write-Host "Total remote-tracking branches: $total"

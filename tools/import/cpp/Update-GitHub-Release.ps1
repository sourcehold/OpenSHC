param(
    [bool]$ClearCppFiles = $false
)

$ErrorActionPreference = "Stop"

$TAG = "latest-sarif"
$SHA = git rev-parse --short --verify HEAD
$CppDir = "tmp\ghidra-cpp"

Write-Host "Using SHA: $SHA"

if ($ClearCppFiles) {
    rm -R $CppDir
}

# Generate cpp files, assuming SARIF file already exists
& "tools\import\cpp\generateassetfiles.ps1" -SHA $SHA -CppDir $CppDir


# Remove all existing release assets
$assets = gh release view $TAG `
    --repo sourcehold/OpenSHC `
    --json assets `
    --jq ".assets[].name"

foreach ($asset in $assets) {
    if ($asset) {
        gh release delete-asset $TAG $asset `
            --repo sourcehold/OpenSHC `
            --yes
    }
}


# Upload the two new assets
gh release upload $TAG `
    --repo sourcehold/OpenSHC `
    "cpp-$SHA.zip" `
    "sarif-$SHA.zip" `
    --clobber

$FullSHA = git rev-parse --verify HEAD
$SHA = git rev-parse --short --verify HEAD
$Date = Get-Date -Format "yyyy-MM-dd"

# Get the release message/body
$content = gh release view $TAG `
    --repo sourcehold/OpenSHC `
    --json body `
    --jq ".body"

# Update the date
$content = $content -replace `
    '\*\*LAST UPDATED: \d{4}-\d{2}-\d{2}\*\*',
    "**LAST UPDATED: $Date**"

# Update the commit SHA
$content = $content -replace `
    'https://github\.com/sourcehold/OpenSHC/tree/[a-f0-9]+',
    "https://github.com/sourcehold/OpenSHC/tree/$FullSHA"

$content = $content -replace `
    'https://github\.com/sourcehold/OpenSHC/commit/[a-f0-9]+',
    "https://github.com/sourcehold/OpenSHC/commit/$FullSHA"


$content | gh release edit $TAG --repo sourcehold/OpenSHC --notes-file -
# Writes the .cpp files of every function this branch touched but did not finish (status neither
# 100% nor 0.0%) to cmake/openshc-sources.txt.local. Run from the repository root.
param(
    [string]$Base = "main",
    [string]$StatusFile = "status/addresses-SHC-3BB0A8C1.txt",
    [string]$SourceRoot = "src/OpenSHC",
    [string]$Destination = "cmake/openshc-sources.txt.local"
)

$lines = git diff $Base HEAD -- $StatusFile | Where-Object { $_.StartsWith("+SHC") -and (-not $_.Contains("| 100")) -and (-not $_.Contains("| 0.0%")) } | ForEach-Object { $_.SubString(1) }

# address -> status line
$wanted = @{}
foreach ($line in $lines) {
    if ($line -match "^SHC_[0-9A-Fa-f]+_0x([0-9A-Fa-f]+)") {
        $wanted[$matches[1].ToUpper()] = $line
    }
}

$root = (Get-Location).Path
$files = New-Object 'System.Collections.Generic.SortedSet[string]' ([System.StringComparer]::Ordinal)
$found = @{}

# A single .cpp can hold several // FUNCTION: lines, so every match in every file is checked.
Get-ChildItem -Path $SourceRoot -Recurse -Filter *.cpp | Select-String -Pattern "//\s*FUNCTION:\s*\S+\s+0x([0-9A-Fa-f]+)" | ForEach-Object {
    $address = $_.Matches[0].Groups[1].Value.ToUpper()
    if ($wanted.ContainsKey($address)) {
        $found[$address] = $true
        [void]$files.Add($_.Path.Substring($root.Length + 1).Replace("\", "/"))
    }
}

foreach ($address in ($wanted.Keys | Sort-Object)) {
    if (-not $found.ContainsKey($address)) {
        Write-Warning "no .cpp found for: $($wanted[$address])"
    }
}

$target = Join-Path $root $Destination
$text = if ($files.Count -gt 0) { ($files -join "`n") + "`n" } else { "" }
[System.IO.File]::WriteAllText($target, $text, (New-Object System.Text.UTF8Encoding $false))

Write-Host "$($wanted.Count) incomplete functions -> $($files.Count) files written to $Destination"

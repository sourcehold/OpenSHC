param(
    [Parameter(Mandatory = $false)]
    [string]$Sarif = "Stronghold Crusader.exe.sarif",
    [string]$OutputDir = "src",
    [bool]$ClearCache = $true,
    [bool]$OverwriteAll = $true,
    [bool]$VerboseLogging = $false,
    [bool]$MakeBackup = $true,
    [bool]$Interactive = $false,
    [bool]$DryRun = $false,
    [bool]$GenerateSarif = $false,
    [string]$ScriptPath = "tools\import\ghidra-importer.py"
)

. .\tools\import\utils\backup-item.ps1

$pyArgs = New-Object System.Collections.Generic.List[System.String]
if ($Interactive) {
    # Useful for debugging purposes. Exit the interpreter to continue the export
    $pyArgs += "-i"
}

$pyArgs += "$ScriptPath"

$pyArgs += "--sarif"
$pyArgs += $Sarif

$pyArgs += "--output-dir"
$pyArgs += "$OutputDir"

if ($OverwriteAll) {
    $pyArgs += "--overwrite-all"
} else {
    $pyArgs += "--no-overwrite-all"
}
if ($ClearCache) {
    $pyArgs += "--clear-cache"
} else {
    $pyArgs += "--no-clear-cache"
}
if ($VerboseLogging) {
    $pyArgs += "--verbose"
}
if ($DryRun) {
    $pyArgs += "--dry-run"
}

if ($DryRun) {
    # Execute the export without writing any files to disk (note this still caches the conversion from ghidra to IR)
    & python $pyArgs
} else {
    
    Write-Output "Backing up or deleting existing hpp files"
    # Backup or delete existing hpp files
    $hppFiles = Get-ChildItem -File -Recurse "$OutputDir\OpenSHC\*.hpp" | Where-Object {$_.Name -ne "string-literals.hpp"} | Where-Object {$_.Name -ne "string-macros.hpp"}
    if ($MakeBackup) {
        $hppFiles | Backup-Item -Move $true
    } else {
        $hppFiles | Remove-Item
    }

    if($GenerateSarif) {
        Write-Output "Generating sarif file from gzf"
        & python .\tools\import\gzftosarif.py --sarif $Sarif
    }

    Write-Output "Converting sarif to .hpp files"
    # Execute the export
    & python $pyArgs

    Write-Output "Applying clang-format"
    # Efficiently format all hpp files by providing a file list to clang-format
    $FileListFile = New-TemporaryFile
    Get-ChildItem -File -Recurse "$OutputDir\*.hpp" | ForEach-Object { $_.FullName} | Join-String -Separator `n | Set-Content -Path $FileListFile
    clang-format -i @$FileListFile

    Write-Output "Updating status tracker"
    # Update table of progress
    python status\extract_header_and_update.py src\precomp\addresses-SHC-3BB0A8C1.hpp
}


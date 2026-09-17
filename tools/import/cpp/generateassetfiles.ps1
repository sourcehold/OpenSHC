param(
    [Parameter(Mandatory = $true)]
    [string]$SHA,

    [Parameter(Mandatory = $true)]
    [string]$CppDir
)

$ErrorActionPreference = "Stop"


# Create SARIF ZIP
Write-Host "Writing 'Stronghold Crusader.exe.sarif' to 'sarif-$SHA.zip'"

7z a `
    -tzip `
    -mm=LZMA `
    -mx=9 `
    "sarif-$SHA.zip" `
    "Stronghold Crusader.exe.sarif"



Write-Host "Generating cpp files in '$CppDir'"
# Generate C++ files
ghidra-cpp namespace `
    --gzf "Stronghold Crusader.exe.gzf" `
    --name OpenSHC `
    --post-processor 'replace("_HoldStrong", "OpenSHC")' `
    --output-dir "$CppDir\src" `
    --recursive `
    --preserve-namespaces

Write-Output "Applying clang-format to cpp files"
# Efficiently format all hpp files by providing a file list to clang-format
$FileListFile = New-TemporaryFile
Get-ChildItem -File -Recurse "$CppDir\src\*.cpp" | ForEach-Object { $_.FullName} | Join-String -Separator `n | Set-Content -Path $FileListFile
clang-format -i @$FileListFile

# Create C++ ZIP
Write-Host "Exporting cpp files in '$CppDir' to 'cpp-$SHA.zip'"

Push-Location $CppDir
try {
    7z a `
        -tzip `
        -mm=LZMA `
        -mx=9 `
        "cpp-$SHA.zip" `
        "src\"
}
finally {
    Pop-Location
}

Move-Item "$CppDir\cpp-$SHA.zip" ".\cpp-$SHA.zip" -Force
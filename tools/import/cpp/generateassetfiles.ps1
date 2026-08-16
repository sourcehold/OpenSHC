param(
    [Parameter(Mandatory = $true)]
    [string]$SHA,

    [Parameter(Mandatory = $true)]
    [string]$CppDir
)

$ErrorActionPreference = "Stop"

# Generate C++ files
ghidra-cpp namespace `
    --gzf "Stronghold Crusader.exe.gzf" `
    --name OpenSHC `
    --post-processor 'replace("_HoldStrong", "OpenSHC")' `
    --output-dir "$CppDir\src" `
    --recursive `
    --preserve-namespaces


# Create SARIF ZIP
Write-Host "Writing 'Stronghold Crusader.exe.sarif' to 'sarif-$SHA.zip'"

7z a `
    -tzip `
    -mm=LZMA `
    -mx=9 `
    "sarif-$SHA.zip" `
    "Stronghold Crusader.exe.sarif"


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
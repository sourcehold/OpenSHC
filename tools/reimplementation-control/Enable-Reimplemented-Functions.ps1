function Enable-Reimplemented-Functions {
    param(
        [string]$AddressFilter = "",
        [string]$CppFilesFilter = "",
        [bool]$CppFilesFilterRecurse = $false,
        [bool]$Enable = $true
    )
    if ("" -eq $CppFilesFilter) {
        $CppFilesFilter = "src\OpenSHC\*.cpp"
        $CppFilesFilterRecurse = $true
    }
    if ("" -eq $AddressFilter) {
        $AddressFilter = "(0x[0-9A-Za-z]+)"
    }
    $funcFiles = Get-ChildItem .\src\OpenSHC\*.func.hpp -Recurse
    $cppFiles = Get-ChildItem $CppFilesFilter
    if ($CppFilesFilterRecurse) {
        $cppFiles = Get-ChildItem $CppFilesFilter -Recurse
    }
    $cppFiles | Select-String -Pattern "//\s*FUNCTION:\s* STRONGHOLDCRUSADER \s*$AddressFilter" | ForEach-Object {
        $address = $_.Matches[0].Groups[1].Value
        $funcFiles |
            Where-Object { $null -ne (Select-String -Path $_ -Pattern "$address") } |
            ForEach-Object {
                (Get-Content -Path $_ -Raw) -replace "(?s)(MACRO_FUNCTION_RESOLVER\b(?:(?!MACRO_FUNCTION_RESOLVER).)*?),\s*$(-not $Enable)(\s*, Address::SHC_3BB0A8C1_$address)", "`$1, $($Enable)`$2" |
                    Set-Content -Path $_
            }
    }
}

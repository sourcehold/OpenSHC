param(
    [string]$HppFiles = ".\src\OpenSHC\Globals\*.hpp",
    [bool]$Enable = $true
)

function Enable-Reimplemented-Data {
    param(
        [string]$HppFiles = ".\src\OpenSHC\Globals\*.hpp",
        [bool]$Enable = $true
    )
    $target = "$(-not $Enable)".ToLower()
    $replacement = "$($Enable)".ToLower()
    Get-ChildItem -Path $HppFiles |
        ForEach-Object {
            Set-Content -NoNewLine -Path $_ -Value ((Get-Content -Path $_ -Raw) -replace 
                "MACRO_STRUCT_RESOLVER(.*), $target,","MACRO_STRUCT_RESOLVER`$1, $replacement,")}
}

if ($MyInvocation.InvocationName -ne '.') {
    Enable-Reimplemented-Data -HppFiles $HppFiles -Enable $Enable
}

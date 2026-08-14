<#
.SYNOPSIS
Activates or deactivates the global resolvers of a function.

.DESCRIPTION
Finds a function by address, name, or namespace-qualified name via Get-Function-Data.ps1 and activates or deactivates
the global resolvers of a function. This is meant to aid during reimplementation, since Globals can add a lot of noise
if not activated.
Verbose output can be enabled with -Verbose.

.PARAMETER Query
Function lookup query:
- 0x[hex address] or [hex address]
- Namespace::Function
- Function

.PARAMETER Enable
Whether to enable or disable the global resolvers of the function.

.PARAMETER Partial
Allows partial function name matches.

.EXAMPLE
.\script.ps1 -Query 1234ABCD -Enable $True

.EXAMPLE
.\script.ps1 -Query Namespace::Function -Enable $False -Verbose

.EXAMPLE
.\script.ps1 -Query Func -Partial -Enable $False

.OUTPUTS
Nothing. Changes the files.
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$Query,

    [Parameter(Mandatory = $true)]
    [boolean]$Enable,

    [switch]$Partial
)

function Fail {
    param(
        [string]$Message
    )
    Write-Host $Message
    exit 1
}

#
# Main
#

# Use project root as working directory
Set-Location (Join-Path $PSScriptRoot "..\..")
Write-Verbose "Working directory: $pwd"

Write-Verbose "Query: $Query"
Write-Verbose "Allow partial function match: $Partial"
Write-Verbose "Enable: $Enable"

$enabled = $Enable.ToString().ToLower()
Write-Verbose "Enabled string: $enabled"

$functionData = & "$PSScriptRoot/Get-Function-Data.ps1" -Query $Query -Partial:$Partial
if ($LASTEXITCODE -ne 0) {
    Fail "Get-Function-Data.ps1 failed to determine function data."
}
if (-not $functionData) {
    Fail "No function data object received for '$Query'."
}
Write-Verbose "Function data:`n$($functionData | Out-String)"

if (-not $functionData.ImplementationFileExists) {
    Fail "No implementation file found for '$Query': $($functionData.ImplementationFile)"
}

$globalsIncludeRegex = '#include\s+"OpenSHC/Globals/([^"]+\.hpp)"'
Write-Verbose "Globals Include Regex: $globalsIncludeRegex"
$globalsFiles = @(Get-Content $functionData.ImplementationFile | ForEach-Object {
    if ($_ -match $globalsIncludeRegex) {
        return "./src/OpenSHC/Globals/$($Matches[1])"
    }
})
Write-Verbose "Globals Files:`n$($globalsFiles | Out-String)"

$regexResolver = "(?s)(?<=MACRO_STRUCT_RESOLVER\s*\([^(]*[^;]*?,\s*)(true|false)"
Write-Verbose "Regex Struct Resolver: $regexResolver"
foreach ($file in $globalsFiles) {
    $content = Get-Content $file -Raw
    if (-not $content -match $regexResolver) {
        Fail "Resolver not found in file '$file'."
    }
    $content = $content -replace $regexResolver, $enabled
    Set-Content $file $content -NoNewline
}

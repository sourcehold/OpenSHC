<#
.SYNOPSIS
Creates an empty implementation file for a function.

.DESCRIPTION
Finds a function by address, name, or namespace-qualified name via Get-Function-Data.ps1 and creates an empty
implementation file. The file still needs to be formatted. It fails if the implementation file already exists.
Verbose output can be enabled with -Verbose.

.PARAMETER Query
Function lookup query:
- 0x[hex address] or [hex address]
- Namespace::Function
- Function

.PARAMETER Partial
Allows partial function name matches.

.EXAMPLE
.\script.ps1 -Query 1234ABCD

.EXAMPLE
.\script.ps1 -Query Namespace::Function -Verbose

.EXAMPLE
.\script.ps1 -Query Func -Partial

.OUTPUTS
Relative path to the implementation file.
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$Query,

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

$functionData = & "$PSScriptRoot/Get-Function-Data.ps1" -Query $Query -Partial:$Partial
if ($LASTEXITCODE -ne 0) {
    Fail "Get-Function-Data.ps1 failed to determine function data."
}
if (-not $functionData) {
    Fail "No function data object received for '$Query'."
}
Write-Verbose "Function data:`n$($functionData | Out-String)"

if ($functionData.ImplementationFileExists) {
    Fail "Implementation file already exists for '$Query': $($functionData.ImplementationFile)"
}

$content = @(
    "#include ""../$(Split-Path $functionData.FuncHeader -Leaf)""",
    "",
    @($functionData.Namespaces | ForEach-Object { "namespace $_ {" }),
    "",
    "// FUNCTION: STRONGHOLDCRUSADER 0x$($functionData.Address)",
    $functionData.Signature,
    "{}",
    "",
    @($functionData.Namespaces | ForEach-Object { "}" }),
    ""
)
Write-Verbose "Content:`n`n$($content | Out-String)"
Set-Content -Path $functionData.ImplementationFile -Value $content

return $functionData.ImplementationFile

<#
.SYNOPSIS
Resolves function information from the project source tree.

.DESCRIPTION
Finds a function by address, name, or namespace-qualified name and returns metadata
such as its signature, source files, address, and implementation status.
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
PSCustomObject containing resolved function metadata.
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

function Convert-RelativePathToUnix {
    param(
        [string]$Path
    )
    Write-Verbose "Convert-RelativePathToUnix"
    Write-Verbose "Path: $Path"
    return ($Path -replace "\\", "/")
}

function Find-TextInFiles {
    param(
        [string]$Text,
        [string]$PathPattern
    )
    Write-Verbose "Find-TextInFiles"
    Write-Verbose "Text: $Text"
    Write-Verbose "Pattern: $PathPattern"

    $arguments = @(
        "/S"
        "/M"
        '/C:' + $Text
        $PathPattern
    )
    $results = @(& findstr.exe @arguments)
    if ($LASTEXITCODE -gt 1) {
        Fail "findstr failed with exit code $LASTEXITCODE"
    }

    Write-Verbose "Exit code: $LASTEXITCODE"
    Write-Verbose "Matches: $($results.Count)"
    return @($results | Resolve-Path -Relative)
}

function Get-SingleResult {
    param(
        [array]$Results,
        [string]$Description
    )
    Write-Verbose "Get-SingleResult"
    Write-Verbose "Description: $Description"
    Write-Verbose "Results: $($Results.Count)"

    if ($Results.Count -eq 1) {
        return $Results[0]
        
    }
    elseif ($Results.Count -eq 0) {
        Fail "$Description`n`nNo matches found."
    }
    else {
        $message = @(
            $Description
            ""
            "Multiple matches found:"
            $Results
        ) -join "`n"
        Fail $message
    }
}

function Search-FunctionData {
    [CmdletBinding()]
    param(
        [string]$FuncHeaderPath,

        [Parameter(Mandatory, ParameterSetName = 'ByAddress')]
        [string]$Address,

        [Parameter(Mandatory, ParameterSetName = 'ByFunction')]
        [string]$Function
    )
    Write-Verbose "Search-FunctionData"



    $funcHeaderContent = Get-Content -Path $FuncHeaderPath -Raw
    switch ($PSCmdlet.ParameterSetName) {
        'ByAddress' {
            Write-Verbose "Try extracting function data from $FuncHeaderPath using $Address."
            $regexResolver = "(?s)MACRO_FUNCTION_RESOLVER\s*\(([^(]*)[^;]*?(true|false),\s*Address::SHC_3BB0A8C1_0x$([regex]::Escape($Address))[^;]*?\)\s*([A-Za-z_]\w*)\s*;"
            Write-Verbose "Regex: $regexResolver"
            if ($funcHeaderContent -match $regexResolver) {
                $returnType = $Matches[1].Trim()
                $enabled = ($Matches[2].Trim() -eq "true")
                $Function = $Matches[3]
            }
            else {
                Fail "Address reference disappeared while resolving:`n$FuncHeaderPath"
            }
        }
        'ByFunction' {
            Write-Verbose "Try extracting function data from $FuncHeaderPath using $Function."
            $regexResolver = "(?s)MACRO_FUNCTION_RESOLVER\s*\(([^(]*)[^;]*?(true|false),\s*Address::SHC_3BB0A8C1_0x([0-9A-Fa-f]+)[^;]*?\)\s*([A-Za-z_]?\w*$([regex]::Escape($Function))\w*)\s*;"
            Write-Verbose "Regex: $regexResolver"
            if ($funcHeaderContent -match $regexResolver) {
                $returnType = $Matches[1].Trim()
                $enabled = ($Matches[2].Trim() -eq "true")
                $Address = $Matches[3]
                if ($Matches[4] -ne $Function) {
                    if ($Partial) {
                        Write-Verbose "Partial function match: $($Matches[4]) vs $Function. Use complete name."
                        $Function = $Matches[4]
                    }
                    else {
                        Fail "Partial function match: $($Matches[4]) vs $Function."
                    }
                }
            }
            else {
                Fail "Function reference disappeared while resolving:`n$FuncHeaderPath"
            }
        }
    }
    Write-Verbose "Return type: $returnType"
    Write-Verbose "Enabled: $enabled"
    Write-Verbose "Address: $Address"
    Write-Verbose "Function: $Function"



    $sourceHeaderPath = $FuncHeaderPath -replace '\.func\.hpp$', '.hpp'
    Write-Verbose "Try extracting data from $sourceHeaderPath."
    $sourceHeaderContent = Get-Content -Path $sourceHeaderPath -Raw
    $namespaces = @(
        [regex]::Matches($sourceHeaderContent, '(?s)\bnamespace\s+([A-Za-z_]\w*)\s+\{') |
        ForEach-Object {
            $_.Groups[1].Value
        }
    )
    Write-Verbose "Namespaces: $namespaces"



    if ($funcHeaderContent -match '(?s)\bnamespace\s+([A-Za-z_]\w*)_Func\s+\{') {
        $potentialClass = $Matches[1]
    }
    else {
        Fail "Did not find _Func namespace in:`n$FuncHeaderPath"
    }
    Write-Verbose "Potential Class: $potentialClass"
    if ($namespaces.Count -gt 0) {
        if ($namespaces[-1] -eq $potentialClass) {
            $potentialClass = $null
        }
    }
    Write-Verbose "Class: $potentialClass"



    $regexFuncSignature = "(?s)($([regex]::Escape($returnType))[^;]*?$([regex]::Escape($Function))\s*\(.*?\)\s*);"
    Write-Verbose "Function Signature Regex: $regexFuncSignature"
    if ($sourceHeaderContent -match $regexFuncSignature) {
        $signature = $Matches[1]
    }
    else {
        Fail "Did not find function signature in:`n$sourceHeaderPath"
    }
    $signature = $signature -replace '\s+', ' '
    if ($potentialClass) {
        $signature = $signature -replace "\b$([regex]::Escape($Function))\b", "$potentialClass::$Function"
    }
    Write-Verbose "Signature: $signature"



    $implementationPath = Join-Path $($FuncHeaderPath -replace '\.func\.hpp$', '')  $($Function + '.cpp')
    Write-Verbose "Implementation Path: $implementationPath"
    $implementationExists = Test-Path $implementationPath
    Write-Verbose "Implementation Exists: $implementationExists"



    $statusRegex = "^\s*SHC_[A-Fa-f0-9]{8}_0x$([regex]::Escape($Address))\s*\|\s*([\d]*\.?[\d]+)\s*%\s*\|\s*(.*)\s*$"
    Write-Verbose "Status Regex: $statusRegex"
    $statusMatch = Select-String -Path "./status/addresses-SHC-3BB0A8C1.txt" -Pattern "$statusRegex"
    if ($null -eq $statusMatch) {
        Fail "Did not find function status in ./status/addresses-SHC-3BB0A8C1.txt"
    }
    $statusNumber = [double]::Parse(
        $statusMatch.Matches.Groups[1].Value,
        [System.Globalization.CultureInfo]::InvariantCulture
    )
    $statusMessage = $statusMatch.Matches.Groups[2].Value
    Write-Verbose "Status Number: $statusNumber"
    Write-Verbose "Status Message: $statusMessage"


    
    return [PSCustomObject]@{
        Namespaces               = $namespaces
        Class                    = $potentialClass
        Function                 = $Function
        Address                  = $Address
        Enabled                  = $enabled
        Signature                = $signature
        SourceHeader             = Convert-RelativePathToUnix -Path $sourceHeaderPath
        FuncHeader               = Convert-RelativePathToUnix -Path $FuncHeaderPath
        ImplementationFile       = Convert-RelativePathToUnix -Path $implementationPath
        ImplementationFileExists = $implementationExists
        ImplementationStatus     = $statusNumber
        ImplementationStatusMsg  = $statusMessage
    }
}

function Resolve-Hex {
    param(
        [string]$Hex
    )
    Write-Verbose "Resolving address: $Hex"

    $funcHeaders = Find-TextInFiles -Text "Address::SHC_3BB0A8C1_0x$Hex" -PathPattern "src/*.func.hpp"
    $headerFile = Get-SingleResult -Results $funcHeaders -Description "Searching address $Hex"

    return Search-FunctionData -FuncHeaderPath $headerFile -Address $Hex
}

# TODO?: Might easily find a lot on generic names. Add other restriction?
# TODO?: As generic search also not really useful, since it is case sensitive and does not return the matched words
function Resolve-Function {
    param(
        [string]$Function
    )
    Write-Verbose "Resolving function '$Function'"

    $funcHeaders = Find-TextInFiles -Text "$Function" -PathPattern "src/*.func.hpp"
    $headerFile = Get-SingleResult -Results $funcHeaders -Description "Searching function '$Function'"

    return Search-FunctionData -FuncHeaderPath $headerFile -Function $Function
}

function Resolve-NamespaceAndFunction {
    param(
        [string]$Namespace,
        [string]$Function
    )
    Write-Verbose "Resolving namespace '$Namespace' and function '$Function'"

    $funcHeaders = Find-TextInFiles -Text "$Function" -PathPattern "src/*$Namespace.func.hpp"
    $headerFile = Get-SingleResult -Results $funcHeaders -Description "Searching namespace '$Namespace' and function '$Function'"

    return Search-FunctionData -FuncHeaderPath $headerFile -Function $Function
}

#
# Main resolver
#

# Use project root as working directory
Set-Location (Join-Path $PSScriptRoot "..\..")
Write-Verbose "Working directory: $pwd"

Write-Verbose "Query: $Query"
Write-Verbose "Allow partial function match: $Partial"

if ($Query -match '^(?:0x)?([0-9A-Fa-f]{8})$') {
    Resolve-Hex -Hex $Matches[1].ToUpper()
    return
}

if ($Query -match '^([A-Za-z_]\w*)::([A-Za-z_]\w*)$') {
    Resolve-NamespaceAndFunction -Namespace $Matches[1] -Function $Matches[2]
    return
}

if ($Query -match '^([A-Za-z_]\w*)$') {
    Resolve-Function -Function $Matches[1]
    return
}

Fail "Invalid query format`n`n$Query`n`nExpected: 0x[hex] | Namespace::Function | Function" 

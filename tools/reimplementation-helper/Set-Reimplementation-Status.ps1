function Set-Reimplementation-Status-From-File {
    param(
        [string]$File = "cmake/openshc-sources.txt.local",
        [string]$Status = "100.0%",
        [string]$Message = "Reimplemented",
        [string]$StatusFile = "status/addresses-SHC-3BB0A8C1.txt"
    )

    $statusContents = Get-Content -Raw -Path $StatusFile

    $files = Get-Content -Path $File | Get-Item

    $files | ForEach-Object {
        Get-Content -Path $_
    } | ForEach-Object {
        $line = $_
        if($line -match "FUNCTION: STRONGHOLDCRUSADER 0x([A-Za-z0-9]+)") {
            $match = "0x$($matches[1].ToUpper())"
            $needle = "SHC_3BB0A8C1_$($match) | 0.0% | Pending"
            $haystack = "SHC_3BB0A8C1_$($match) | $($Status) | $($Message)"
            $statusContents = $statusContents.Replace($needle, $haystack)
        }
    }

    $statusContents | Set-Content -Path $StatusFile -NoNewLine
}
function Backup-Item {
    param(
        [Parameter(ValueFromPipeline = $true, Mandatory = $true)]
        [System.IO.FileInfo]$InputObject,

        [string]$Destination = ".\tmp\backup",
        [bool]$Move = $false
    )

    begin {
        $today = Get-Date -Format "yyyy-MM-dd"
        $counter = 1

        while (Test-Path "$Destination\$today-$($counter.ToString('000'))") {
            $counter++
        }

        $basePath = "$Destination\$today-$($counter.ToString('000'))"
    }

    process {

        $relativePath = Resolve-Path -Path $InputObject.FullName -Relative
        $targetPath = Join-Path $basePath $relativePath

        New-Item -ItemType Directory -Path (Split-Path $targetPath) -Force | Out-Null
        if ($Move) {
            Move-Item -Path $InputObject.FullName -Destination $targetPath -Force
        } else {
            Copy-Item -Path $InputObject.FullName -Destination $targetPath -Force
        }
        
    }
}

function Restore-Items-From-Backup-Folder {
    param(
        [string]$Source = ".\tmp\backup\*",
        [bool]$Destination = ".\src\",
        [string]$Filter = "**\*"
    )
    $src = Get-ChildItem -Path .\tmp\backup\*  | Sort-Object -Descending | Select-Object -Index 0
    $files = Get-ChildItem -Path "$src\$Filter" -Recurse

    $files | 
        ForEach-Object {
            $p = Resolve-Path -Path $_ -Relative -RelativeBasePath $src; 
            $p = "$Destination$p";
            New-Item -Type Directory -Path "$(Split-Path $p)" -Force; 
            Copy-Item -Path $_ -Destination $p -Force
        }
}
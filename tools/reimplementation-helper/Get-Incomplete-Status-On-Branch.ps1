git diff main HEAD .\status\addresses-SHC-3BB0A8C1.txt | Where-Object {$_.StartsWith("+SHC") -and (-not $_.Contains("| 100"))} | ForEach-Object {$_.SubString(1)}

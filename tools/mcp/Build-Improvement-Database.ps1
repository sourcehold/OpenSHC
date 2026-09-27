function Build-True-Source-File-List {
    param (
        [string]$Destination = "tmp\true-source-file-list.txt"
    )
    $files = git ls-tree --full-tree --name-only -r main | Select-String -Pattern "src/OpenSHC/.*[.]cpp"
    $files | Set-Content -Path $Destination
}

function Build-Entries {
    param (
        [string]$TrueFileList = "tmp\true-source-file-list.txt",
        [string]$GhidraCppSrc = "tmp\ghidra-cpp\"
    )

    $files = Get-Content -Path $TrueFileList | Where-Object {
        $null -ne (Get-Item -Path "$($GhidraCppSrc)/$_" -ErrorAction SilentlyContinue)
    }

    $files | ForEach-Object {
        $Address = "<unknown>"
        $matchingContents = Get-Content -Raw -Path "$_"
        if($matchingContents -match "// FUNCTION: STRONGHOLDCRUSADER 0x([0-9A-Za-z]+)") {
            $Address = "0x$($matches[1].ToLower())"
        }

        $FuncName = (("$_".Split("/"))[1..100]) | Join-String -Separator "::"
        $FuncName = $FuncName.Substring(0, $funcName.Length - 4)

        [ordered]@{
            File = "$_";
            Address = "$Address";
            FuncName = $FuncName;
            Matching = $matchingContents;
            Raw = Get-Content -Raw -Path "$($GhidraCppSrc)/$_";
        }
    }
}

function Build-Improvement-Database {
    param (
        [string]$Destination = "tmp\improvement-database.yml",
        [string]$TrueFileList = "tmp\true-source-file-list.txt",
        [string]$GhidraCppSrc = "tmp\ghidra-cpp\"
    )

    Build-Entries -TrueFileList $TrueFileList -GhidraCppSrc $GhidraCppSrc | ConvertTo-Yaml | Set-Content -Path $Destination
}
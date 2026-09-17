function Add-All-Cpp-To-Cmake {
    param(
        [string]$Destination = "cmake\openshc-sources.txt.local"
    )
    Get-ChildItem .\src\OpenSHC\*.cpp -Recurse |
        Resolve-Path -Relative |
        ForEach-Object { "$_".Substring(2).Replace("\", "/") } |
        Join-String -Separator "`n" |
        Set-Content -Path "$Destination"
}

function Add-All-Reimplementations-To-Cmake {
	git ls-tree --full-tree --name-only -r main | Select-String -Pattern "src/OpenSHC/.*[.]cpp" > .\cmake\openshc-sources.txt.local
}

if ($MyInvocation.InvocationName -ne '.') {
	 Add-All-Reimplementations-To-Cmake
}

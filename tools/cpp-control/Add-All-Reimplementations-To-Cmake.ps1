function Add-All-Reimplementations-To-Cmake {
    param(
        [string]$Destination = "cmake\openshc-sources.txt"
    )
    Get-ChildItem .\src\OpenSHC\*.cpp -Recurse |
        Resolve-Path -Relative |
        ForEach-Object { "$_".Substring(2).Replace("\", "/") } |
        Join-String -Separator "`n" |
        Set-Content -Path "$Destination"
}
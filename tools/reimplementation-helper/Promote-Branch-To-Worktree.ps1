param (
	[string]$Branch,
	[string]$Path
)

$ErrorActionPreference = "Stop"

$CurrentBranch = git branch --show-current

if ("main" -ne "$CurrentBranch") {Write-Error "Not on 'main'"}

mkdir "$Path"

git branch $Branch

git worktree add "$Path" $Branch

mkdir "$Path\_original"

copy "_original\Stronghold Crusader.exe" "$Path\_original\"

pushd "$Path"

git submodule update --init --recursive

reccmp\dll\setup.bat

git push --set-upstream origin $Branch

.\build.bat RelWithDebInfo OpenSHC.dll

reccmp/dll/run.bat reccmp-reccmp --target STRONGHOLDCRUSADER

popd

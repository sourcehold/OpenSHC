gh pr list --repo https://github.com/sourcehold/OpenSHC --base main --json "headRefName,url" | jq ".[] | select( .headRefName | startswith(\"reimpl/\")) | .url"

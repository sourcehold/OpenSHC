#!/bin/bash

# Letting VS Code search the env did not work for the shebang

WINE_BIN=/usr/bin/wine        # <- adjust if Wine is somewhere else
WINEPATH_BIN=/usr/bin/winepath

# Helper: Transform argument - handles paths and key=value pairs
transform_arg() {
  case "$1" in
    /*)
      # Absolute path
      $WINEPATH_BIN -w "$1"
      ;;
    *=/*)
      # Key=value path
      local key="${1%%=*}"
      local val="${1#*=}"
      echo "$key=$($WINEPATH_BIN -w "$val")"
      ;;
    *)
      # Needed since echo might consume the parameters
      printf '%s\n' "$1"
      ;;
  esac
}

# Helper: Transform semicolon-separated path list to Windows format
winepath_list() {
  local IFS=';'
  local paths=($1)
  local result=()
  for p in "${paths[@]}"; do
    result+=("$(transform_arg "$p")")
  done
  local IFS=';'
  echo "${result[*]}"
}

# Transform paths to Windows format and handle spaces
args=()
for arg in "$@"; do
  out="$(transform_arg "$arg")"
  # Wrap in quotes if contains space
  [[ "$out" == *" "* ]] && out="\"$out\""
  args+=("$out")
done

# Create a temporary batch file with the cmake command
# This avoids quoting hell with cmd /c
# Use /tmp since mktemp may not be available
batch_file="/tmp/cmake_$$.bat"
batch_file_win="$($WINEPATH_BIN -w "$batch_file")"

# Write the batch file
{
  echo "@echo off"

  # Add getting the cmake exe here
  echo 'for /f "tokens=*" %%i in ('\''where cmake'\'') do set CMAKE_EXE=%%i'
  
  # If VSINSTALLDIR is set, embed all MSVC environment variables into the batch
  if [ -n "$VSINSTALLDIR" ]; then
    echo "set VSINSTALLDIR=$(transform_arg "$VSINSTALLDIR")"
    [ -n "$VCINSTALLDIR" ] && echo "set VCINSTALLDIR=$(transform_arg "$VCINSTALLDIR")"
    [ -n "$FrameworkDir" ] && echo "set FrameworkDir=$(transform_arg "$FrameworkDir")"
    [ -n "$FrameworkVersion" ] && echo "set FrameworkVersion=$FrameworkVersion"
    [ -n "$FrameworkSDKDir" ] && echo "set FrameworkSDKDir=$(transform_arg "$FrameworkSDKDir")"
    [ -n "$DevEnvDir" ] && echo "set DevEnvDir=$(transform_arg "$DevEnvDir")"
    [ -n "$INCLUDE" ] && echo "set INCLUDE=$(winepath_list "$INCLUDE")"
    [ -n "$LIB" ] && echo "set LIB=$(winepath_list "$LIB")"
    [ -n "$LIBPATH" ] && echo "set LIBPATH=$(winepath_list "$LIBPATH")"
    [ -n "$PATH" ] && echo "set PATH=$(winepath_list "$PATH")"
  fi
  
  printf -- '"%%CMAKE_EXE%%"'
  for arg in "${args[@]}"; do
    printf -- ' %s' "$arg"
  done
  echo ""
} > "$batch_file"

# Remove the batch file
trap 'rm -f "$batch_file"' EXIT

# Run the batch file through wine
exec "$WINE_BIN" "$batch_file_win"

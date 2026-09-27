@echo off
setlocal EnableDelayedExpansion

:: --------------------------------------------
:: Optional wrapper arguments
:: --------------------------------------------
if /i "%~1"=="--wrap-quiet" (
    set "WRAP_QUIET=1"
    shift
)

:: --- Validate preset parameter (required) ---
if "%~1"=="" (
    if not defined WRAP_QUIET (
        echo [ERROR] Preset not specified.
        echo Usage: %~nx0 [--wrap-quiet] ^<Preset^> [Target]
        echo   ^<Preset^> : Required. The CMake configure/build preset to use.
        echo   [Target] : Optional. The specific target to build. If omitted, the default target will be built.
    )
    exit /b 1
)

set "PRESET=%~1"
set "TARGET=%~2"

:: --- Give this worktree its own PDB server ---
:: mspdbsrv.exe is a per-user singleton keyed on _MSPDBSRV_ENDPOINT_, and every worktree
:: carries its own copy of the toolchain. Sharing one endpoint across worktrees makes
:: cl.exe talk to whichever copy started first and fail with
::   fatal error C1090: PDB API call failed, error code '23'
if not defined _MSPDBSRV_ENDPOINT_ (
    for %%I in ("%~dp0.") do set "_MSPDBSRV_ENDPOINT_=openshc_%%~nxI"
)

:: --- Kill this worktree's mspdbsrv.exe if it's running ---
:: Only ours: killing every instance by image name takes down the PDB server of any other
:: worktree that is building at the same time, which fails their build with C1090.
powershell -NoProfile -Command ^
    "Get-Process mspdbsrv -ErrorAction SilentlyContinue | Where-Object { $_.Path -like '%~dp0*' } | Stop-Process -Force -ErrorAction SilentlyContinue" >nul 2>&1

:: --- Run cmake configure using preset ---
if not defined WRAP_QUIET echo [INFO] Configuring with preset "%PRESET%"...
call .\cmakew --preset "%PRESET%"
if errorlevel 1 (
    if not defined WRAP_QUIET echo [ERROR] CMake configure failed for preset "%PRESET%".
    exit /b 1
)

:: --- Run cmake build using preset ---
if "%TARGET%"=="" (
    if not defined WRAP_QUIET echo [INFO] Building preset "%PRESET%" with default target...
    call .\cmakew --build --preset "%PRESET%"
    if errorlevel 1 (
        if not defined WRAP_QUIET echo [ERROR] CMake build failed for preset "%PRESET%".
        exit /b 1
    )
    if not defined WRAP_QUIET echo Build completed successfully for preset "%PRESET%".
) else (
    if not defined WRAP_QUIET echo [INFO] Building preset "%PRESET%" with target "%TARGET%"...
    call .\cmakew --build --preset "%PRESET%" --target "%TARGET%"
    if errorlevel 1 (
        if not defined WRAP_QUIET echo [ERROR] CMake build failed for preset "%PRESET%" target "%TARGET%".
        exit /b 1
    )
    if not defined WRAP_QUIET echo Build completed successfully for preset "%PRESET%" target "%TARGET%".
)

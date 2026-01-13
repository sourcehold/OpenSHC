@echo off
setlocal EnableDelayedExpansion

:: --- Validate preset parameter (required) ---
if "%~1"=="" (
    echo [ERROR] Preset not specified.
    echo Usage: %~nx0 ^<Preset^> [Target]
    echo   ^<Preset^> : Required. The CMake configure/build preset to use.
    echo   [Target]   : Optional. The specific target to build. If omitted, the default target will be built.
    exit /b 1
)

set "PRESET=%~1"
set "TARGET=%~2"

:: --- Kill mspdbsrv.exe if it's running ---
tasklist | find /I "mspdbsrv.exe" >nul
if not errorlevel 1 (
    echo Stopping mspdbsrv.exe...
    taskkill /f /t /im mspdbsrv.exe >nul
    if errorlevel 1 (
        echo [WARNING] Failed to stop mspdbsrv.exe, continuing...
    )
)

:: --- Run cmake configure using preset ---
echo [INFO] Configuring with preset "%PRESET%"...
call .\cmakew --preset "%PRESET%"
if errorlevel 1 (
    echo [ERROR] CMake configure failed for preset "%PRESET%".
    exit /b 1
)

:: --- Run cmake build using preset ---
if "%TARGET%"=="" (
    echo [INFO] Building preset "%PRESET%" with default target...
    call .\cmakew --build --preset "%PRESET%"
    if errorlevel 1 (
        echo [ERROR] CMake build failed for preset "%PRESET%".
        exit /b 1
    )
    echo Build completed successfully for preset "%PRESET%".
) else (
    echo [INFO] Building preset "%PRESET%" with target "%TARGET%"...
    call .\cmakew --build --preset "%PRESET%" --target "%TARGET%"
    if errorlevel 1 (
        echo [ERROR] CMake build failed for preset "%PRESET%" target "%TARGET%".
        exit /b 1
    )
    echo Build completed successfully for preset "%PRESET%" target "%TARGET%".
)

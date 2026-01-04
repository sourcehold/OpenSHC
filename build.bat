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

:: --- Check for cmake ---
where cmake >nul 2>nul
if errorlevel 1 (
    echo [INFO]  Auto-detecting cmake location using vswhere.
    if not exist "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" (
        echo [ERROR] 'vswhere' not found, cannot locate 'cmake'.
        exit /b 1
    )
    FOR /F "tokens=* USEBACKQ" %%g IN (`"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath -requires Microsoft.VisualStudio.Component.VC.CMake.Project`) do (
        SET "CMAKE=%%g\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin"
    )
    echo [INFO]  Detected: "!CMAKE!"
    if not exist "!CMAKE!" (
        echo [ERROR] 'cmake' is not found in PATH and not found using vswhere.
        exit /b 1
    )
    set "PATH=!CMAKE!;%PATH%"
)

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
cmake --preset "%PRESET%"
if errorlevel 1 (
    echo [ERROR] CMake configure failed for preset "%PRESET%".
    exit /b 1
)

:: --- Run cmake build using preset ---
if "%TARGET%"=="" (
    echo [INFO] Building preset "%PRESET%" with default target...
    cmake --build --preset "%PRESET%"
    if errorlevel 1 (
        echo [ERROR] CMake build failed for preset "%PRESET%".
        exit /b 1
    )
    echo Build completed successfully for preset "%PRESET%".
) else (
    echo [INFO] Building preset "%PRESET%" with target "%TARGET%"...
    cmake --build --preset "%PRESET%" --target "%TARGET%"
    if errorlevel 1 (
        echo [ERROR] CMake build failed for preset "%PRESET%" target "%TARGET%".
        exit /b 1
    )
    echo Build completed successfully for preset "%PRESET%" target "%TARGET%".
)

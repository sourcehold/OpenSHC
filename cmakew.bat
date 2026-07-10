@echo off
setlocal EnableDelayedExpansion

:: --- Optional wrapper arguments
set "ARGS=%*"
if /i "%~1"=="--wrap-quiet" (
    set "WRAP_QUIET=1"
    set "ARGS=!ARGS:--wrap-quiet=!"
)

:: --- Check if cmake is in PATH ---
where cmake >nul 2>nul
if errorlevel 1 (
    if not defined WRAP_QUIET echo [INFO] Auto-detecting cmake location using vswhere.

    if not exist "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" (
        if not defined WRAP_QUIET echo [ERROR] 'vswhere' not found, cannot locate 'cmake'.
        exit /b 1
    )

    :: Try to locate CMake in latest VS installation
    FOR /F "tokens=* USEBACKQ" %%g IN (`"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath -requires Microsoft.VisualStudio.Component.VC.CMake.Project`) do (
        SET "CMAKE=%%g\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin"
    )

    :: If not found, try latest Build Tools installation
    if not exist "!CMAKE!" (
        FOR /F "tokens=* USEBACKQ" %%g IN (`"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath -requires Microsoft.VisualStudio.Component.VC.CMake.Project -products Microsoft.VisualStudio.Product.BuildTools`) do (
            SET "CMAKE=%%g\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin"
        )
    )

    if not exist "!CMAKE!" (
        if not defined WRAP_QUIET echo [ERROR] 'cmake' not found in PATH and not found using vswhere.
        exit /b 1
    )

    if not defined WRAP_QUIET echo [INFO] Detected: "!CMAKE!"
    set "PATH=!CMAKE!;%PATH%"
)

:: --- Proxy all arguments to actual CMake ---
cmake !ARGS!
exit /b %errorlevel%

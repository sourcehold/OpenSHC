@echo off
setlocal EnableDelayedExpansion

:: --- Validate task parameter (clean, build, rebuild) ---
if "%~1"=="" (
    echo [ERROR] Task not specified.
    echo Usage: %~nx0 [clean^|build^|rebuild] [BuildType]
    exit /b 1
)

set "TASK=%~1"

if /I not "%TASK%"=="clean" if /I not "%TASK%"=="build" if /I not "%TASK%"=="rebuild" (
    echo [ERROR] Invalid task: "%TASK%"
    echo Valid tasks are: clean, build, rebuild
    exit /b 1
)

:: --- Validate build type parameter (must be only letters) ---
if "%~2"=="" (
    echo [ERROR] Build type not specified.
    echo Usage: %~nx0 [clean^|build^|rebuild] [BuildType]
    exit /b 1
)

:: --- Validate that is is at least all letters, also need to use "." hack due to piping issue with *$ in findstr (. consumes \r) ---
echo %~2 | findstr /R "^[a-zA-Z][a-zA-Z]*.$" >nul
if errorlevel 1 (
    echo [ERROR] Invalid build type: "%~2"
    echo It must only contain letters ^(e.g., Debug, Release^).
    exit /b 1
)

:: --- Set build directory ---
set "BUILD_DIR=build-%~2"

:: --- Clean build directory if task is clean or rebuild ---
if /I not "%TASK%"=="build" (
    if exist "%BUILD_DIR%" (
        echo Cleaning build directory "%BUILD_DIR%"...
        rmdir /S /Q "%BUILD_DIR%"
        if errorlevel 1 (
            echo [ERROR] Failed to clean build directory "%BUILD_DIR%".
            exit /b 1
        )
        echo Clean completed successfully.
    ) else (
        echo Build directory "%BUILD_DIR%" does not exist. Nothing to clean.
    )
)

:: --- If task is clean only, exit after cleaning ---
if /I "%TASK%"=="clean" (
    exit /b 0
)

:: --- Check and load old environment into context ---
set "VSVARS=MSVC1400\vsvars32-portable.bat"
if not exist "%VSVARS%" (
    echo [ERROR] Could not find environment setup script: %VSVARS%
    exit /b 1
)
call "%VSVARS%"
if errorlevel 1 (
    echo [ERROR] Failed to execute: %VSVARS%
    exit /b 2
)

:: --- Check for cmake ---
where cmake >nul 2>nul
if errorlevel 1 (
    echo [INFO]  Auto-detecting cmake location using vswhere.
    if not exist "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" (
        echo [ERROR] 'vswhere' not found, cannot locate 'cmake'.
        exit /b 1
    )
    FOR /F "tokens=* USEBACKQ" %%g IN (`"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath -requires Microsoft.VisualStudio.Component.VC.CMake.Project`) do (SET "CMAKE=%%g\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin")
    echo [INFO]  Detected: "!CMAKE!"
    if not exist "!CMAKE!" (
        echo [ERROR] 'cmake' is not found in PATH and not found using vswhere.
        exit /b 1
    )
    set "PATH=!CMAKE!;%PATH%"
)

:: --- Check for nmake ---
where nmake >nul 2>nul
if errorlevel 1 (
    echo [ERROR] 'nmake' is not found in PATH.
    exit /b 1
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

:: --- Create build directory ---
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%" >nul 2>&1
    if errorlevel 1 (
        echo [ERROR] Failed to create build directory "%BUILD_DIR%".
        exit /b 1
    )
)

:: --- Run cmake and nmake ---
pushd "%BUILD_DIR%"
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=%~2
if errorlevel 1 (
    echo [ERROR] cmake failed.
    popd
    exit /b 1
)

nmake
if errorlevel 1 (
    echo [ERROR] nmake build failed.
    popd
    exit /b 1
)

popd
echo Build completed successfully for "%~2" configuration.

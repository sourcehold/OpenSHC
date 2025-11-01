@echo off
setlocal

:: === Configuration ===
:: Define expected files and their SHA256 hashes
:: Comment out EXE_VANILLA and/or EXE_EXTREME to skip hash check

:: Western 1.41
set "EXE_VANILLA=Stronghold Crusader.exe"
set "HASH_VANILLA=3bb0a8c1e72331b3a30a5aa93ed94beca0081b476b04c1960e26d5b45387ac5a"

:: Western 1.41.1-E
set "EXE_EXTREME=Stronghold_Crusader_Extreme.exe"
set "HASH_EXTREME=55648e6b05d67d37a5773fe699bbb17a2d6ad4de1bb9dbded9a21caef82bd7fb"

:: === Parameter or user input ===
set "INTERACTIVE=0"
if "%~1"=="" set "INTERACTIVE=1"

:: --- Check for Administrator privileges ---
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Administrator privileges required to run this script.
    echo Please run the script as Administrator.
    if "%INTERACTIVE%"=="1" pause
    exit /b 1
)

:: Change working directory to the folder where the script is located
cd /d "%~dp0" || (
    echo [ERROR] Failed to set working directory to script location: %~dp0
    if "%INTERACTIVE%"=="1" pause
    exit /b 1
)

:: Set path or ask for it
if "%INTERACTIVE%"=="1" (
    echo No path provided as parameter.
    set /p "TARGET=Please enter the full path to the folder: "
) else (
    set "TARGET=%~1"
)


:: Trim possible quotes
set "TARGET=%TARGET:"=%"

:: === Path validation ===
if not exist "%TARGET%\" (
    echo [ERROR] Path does not exist or is not a folder: "%TARGET%"
    if "%INTERACTIVE%"=="1" pause
    exit /b 1
)

echo.
echo === Validating Files in "%TARGET%" ===

:: ====================================================
:: === Check 1: Stronghold Crusader.exe (Vanilla)
:: ====================================================
if defined EXE_VANILLA (
    echo Checking "%EXE_VANILLA%"...
    if not exist "%TARGET%\%EXE_VANILLA%" (
        echo [ERROR] Missing file: %EXE_VANILLA%
        if "%INTERACTIVE%"=="1" pause
        exit /b 1
    )

    :: Get SHA256 hash reliably
    for /f "skip=1 delims=" %%H in ('certutil -hashfile "%TARGET%\%EXE_VANILLA%" SHA256') do (
        set "ACTUAL_HASH_VANILLA=%%H"
        goto :gotVanillaHash
    )
    :gotVanillaHash
    set "ACTUAL_HASH_VANILLA=%ACTUAL_HASH_VANILLA: =%"

    if /i not "%ACTUAL_HASH_VANILLA%"=="%HASH_VANILLA%" (
        echo [ERROR] Hash mismatch for Western 1.41 %EXE_VANILLA%
        echo Expected: %HASH_VANILLA%
        echo Found:    %ACTUAL_HASH_VANILLA%
        if "%INTERACTIVE%"=="1" pause
        exit /b 1
    )
    echo [OK] %EXE_VANILLA% hash verified.
    echo.
)

:: ====================================================
:: === Check 2: Stronghold_Crusader_Extreme.exe (Extreme)
:: ====================================================
if defined EXE_EXTREME (
    echo Checking "%EXE_EXTREME%"...
    if not exist "%TARGET%\%EXE_EXTREME%" (
        echo [ERROR] Missing file: %EXE_EXTREME%
        if "%INTERACTIVE%"=="1" pause
        exit /b 1
    )

    :: Get SHA256 hash reliably
    for /f "skip=1 delims=" %%H in ('certutil -hashfile "%TARGET%\%EXE_EXTREME%" SHA256') do (
        set "ACTUAL_HASH_EXTREME=%%H"
        goto :gotExtremeHash
    )
    :gotExtremeHash
    set "ACTUAL_HASH_EXTREME=%ACTUAL_HASH_EXTREME: =%"

    if /i not "%ACTUAL_HASH_EXTREME%"=="%HASH_EXTREME%" (
        echo [ERROR] Hash mismatch for %EXE_EXTREME%
        echo Expected: %HASH_EXTREME%
        echo Found:    %ACTUAL_HASH_EXTREME%
        if "%INTERACTIVE%"=="1" pause
        exit /b 1
    )
    echo [OK] %EXE_EXTREME% hash verified.
    echo.
)

echo All required files passed integrity check.

:: === Remove existing _original safely ===
if exist "_original" (
    attrib -r "_original" 2>nul
    if exist "_original\" (
        rmdir "_original" 2>nul
    ) else (
        del "_original" 2>nul
    )
)

:: === Create symbolic link ===
echo Creating symbolic link "_original" -^> "%TARGET%"
mklink /D "_original" "%TARGET%"
if %errorlevel% neq 0 (
    echo [ERROR] Failed to create symbolic link. Try running as Administrator.
    if "%INTERACTIVE%"=="1" pause
    exit /b 1
)

echo [SUCCESS] Link created successfully.

if "%INTERACTIVE%"=="1" pause

endlocal
exit /b 0

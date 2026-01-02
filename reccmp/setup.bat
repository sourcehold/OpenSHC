@echo off
setlocal

:: === Configuration ===
set "VENV_DIR=.venv"
set "REQ_FILE=requirements.txt"
set "ENV_ACTIVE=0"

:: --- Change working directory to the folder where the script is located ---
cd /d "%~dp0" || (
    echo [ERROR] Failed to set working directory to script location: %~dp0
    call :Cleanup
    exit /b 1
)

:: --------------------------------------------
:: Check if not running in own env
:: --------------------------------------------
if /i "%VIRTUAL_ENV%"=="%CD%\%VENV_DIR%" (
    echo [ERROR] This script is already running inside the target virtual environment.
    exit /b 1
)

:: --------------------------------------------
:: Check for Python installation
:: --------------------------------------------
python --version >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Python is not installed or not in PATH.
    call :Cleanup
    exit /b 1
)
echo [OK] Python is available.

:: --------------------------------------------
:: Create virtual environment
:: --------------------------------------------
echo Creating virtual environment in "%VENV_DIR%"...
python -m venv "%VENV_DIR%"
if %errorlevel% neq 0 (
    echo [ERROR] Failed to create virtual environment.
    call :Cleanup
    exit /b 1
)

:: --------------------------------------------
:: Activate virtual environment
:: --------------------------------------------
call "%VENV_DIR%\Scripts\activate.bat"
if /i not "%VIRTUAL_ENV%"=="%CD%\%VENV_DIR%" (
    echo [ERROR] Failed to activate virtual environment.
    call :Cleanup
    exit /b 1
)
set "ENV_ACTIVE=1"
echo [OK] Virtual environment activated.

:: --------------------------------------------
:: Install requirements
:: --------------------------------------------
if not exist "%REQ_FILE%" (
    echo [ERROR] Requirements file not found: %REQ_FILE%
    call :Cleanup
    exit /b 1
)

echo Installing packages from "%REQ_FILE%"...
pip install -r "%REQ_FILE%"
if %errorlevel% neq 0 (
    echo [ERROR] Failed to install packages.
    call :Cleanup
    exit /b 1
)
echo [OK] All packages installed successfully.

:: --------------------------------------------
:: Normal cleanup
:: --------------------------------------------
call :Cleanup

echo [SUCCESS] Setup complete.
endlocal
exit /b 0

:: --------------------------------------------
:: Cleanup function
:: --------------------------------------------
:Cleanup
if "%ENV_ACTIVE%"=="1" (
    deactivate
    set "ENV_ACTIVE=0"
    echo [OK] Virtual environment deactivated.
)
exit /b 0

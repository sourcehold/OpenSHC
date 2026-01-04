@echo off
setlocal

:: === Configuration ===
set "VENV_DIR=.venv"
set "ENV_ACTIVE=0"
set "CMD_EXIT_CODE=0"

:: --------------------------------------------
:: Change working directory to script location
:: --------------------------------------------
cd /d "%~dp0" || (
    echo [ERROR] Failed to set working directory to script location.
    call :Cleanup
    exit /b 1
)

:: --------------------------------------------
:: Check arguments
:: --------------------------------------------
if "%~1"=="" (
    echo [ERROR] No command provided.
    echo Usage: %~nx0 command [args...]
    call :Cleanup
    exit /b 1
)

:: --------------------------------------------
:: Check virtual environment exists
:: --------------------------------------------
if not exist "%VENV_DIR%\Scripts\activate.bat" (
    echo [ERROR] Virtual environment not found: %VENV_DIR%
    echo Please run the setup script first.
    call :Cleanup
    exit /b 1
)

:: --------------------------------------------
:: Prevent double-activation
:: --------------------------------------------
if /i "%VIRTUAL_ENV%"=="%CD%\%VENV_DIR%" (
    echo [ERROR] Already running inside the target virtual environment.
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
:: Run provided command
:: --------------------------------------------
echo [INFO] Running command: %*
cmd /c %*
set "CMD_EXIT_CODE=%ERRORLEVEL%"
if %CMD_EXIT_CODE% neq 0 (
    echo [ERROR] Command failed with exit code %CMD_EXIT_CODE%.
    call :Cleanup
    exit /b %CMD_EXIT_CODE%
)

:: --------------------------------------------
:: Cleanup
:: --------------------------------------------
call :Cleanup

echo [SUCCESS] Command completed successfully.
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

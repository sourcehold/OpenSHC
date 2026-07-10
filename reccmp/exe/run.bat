@echo off
setlocal

:: === Configuration ===
set "VENV_DIR=.venv"
set "ENV_ACTIVE=0"
set "CMD_EXIT_CODE=0"

:: --------------------------------------------
:: Optional wrapper arguments
:: --------------------------------------------
set "ARGS=%*"
if /i "%~1"=="--wrap-quiet" (
    set "WRAP_QUIET=1"
    set "ARGS=%ARGS:--wrap-quiet=%"
)

:: --------------------------------------------
:: Change working directory to script location
:: --------------------------------------------
cd /d "%~dp0" || (
    if not defined WRAP_QUIET echo [ERROR] Failed to set working directory to script location.
    call :Cleanup
    exit /b 1
)

:: --------------------------------------------
:: Check arguments
:: --------------------------------------------
if "%ARGS%"=="" (
    if not defined WRAP_QUIET (
        echo [ERROR] No command provided.
        echo Usage: %~nx0 [--wrap-quiet] command [args...]
    )
    call :Cleanup
    exit /b 1
)

:: --------------------------------------------
:: Check virtual environment exists
:: --------------------------------------------
if not exist "%VENV_DIR%\Scripts\activate.bat" (
    if not defined WRAP_QUIET (
        echo [ERROR] Virtual environment not found: %VENV_DIR%
        echo Please run the setup script first.
    )
    call :Cleanup
    exit /b 1
)

:: --------------------------------------------
:: Prevent double-activation
:: --------------------------------------------
if /i "%VIRTUAL_ENV%"=="%CD%\%VENV_DIR%" (
    if not defined WRAP_QUIET echo [ERROR] Already running inside the target virtual environment.
    call :Cleanup
    exit /b 1
)

:: --------------------------------------------
:: Activate virtual environment
:: --------------------------------------------
call "%VENV_DIR%\Scripts\activate.bat"
if /i not "%VIRTUAL_ENV%"=="%CD%\%VENV_DIR%" (
    if not defined WRAP_QUIET echo [ERROR] Failed to activate virtual environment.
    call :Cleanup
    exit /b 1
)

set "ENV_ACTIVE=1"
if not defined WRAP_QUIET echo [OK] Virtual environment activated.

:: --------------------------------------------
:: Run provided command
:: --------------------------------------------
if not defined WRAP_QUIET echo [INFO] Running command: %ARGS%
cmd /c %ARGS%
set "CMD_EXIT_CODE=%ERRORLEVEL%"
if %CMD_EXIT_CODE% neq 0 (
    if not defined WRAP_QUIET echo [ERROR] Command failed with exit code %CMD_EXIT_CODE%.
    call :Cleanup
    exit /b %CMD_EXIT_CODE%
)

:: --------------------------------------------
:: Cleanup
:: --------------------------------------------
call :Cleanup

if not defined WRAP_QUIET echo [SUCCESS] Command completed successfully.
exit /b 0

:: --------------------------------------------
:: Cleanup function
:: --------------------------------------------
:Cleanup
if "%ENV_ACTIVE%"=="1" (
    deactivate
    set "ENV_ACTIVE=0"
    if not defined WRAP_QUIET echo [OK] Virtual environment deactivated.
)
exit /b 0

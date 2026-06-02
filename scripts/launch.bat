@echo off
:: Build + run. Human mode: no args (window stays open). Claude mode: --no-pause (clean exit).

set EXE=%~dp0..\project\x64\Release\CoverVidMaker.exe
set START_TIME=%TIME%

:: Build first
call "%~dp0build.bat" --no-pause
if errorlevel 1 (
    echo [ERROR] Build failed. Aborting.
    if not "%1"=="--no-pause" cmd /k
    exit /b 1
)

echo.
echo [RUN] Generating cover videos...
echo ============================================================
echo.

:: Change to repo root so relative paths (media/, dependencies/) resolve correctly
cd /d "%~dp0.."

"%EXE%"

echo.
echo ============================================================
echo [DONE] Start: %START_TIME%  End: %TIME%
echo ============================================================
echo.
if not "%1"=="--no-pause" cmd /k
exit /b 0

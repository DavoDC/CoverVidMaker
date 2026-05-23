@echo off

:: ============================================================
:: CoverVidMaker Launcher
:: ============================================================

set EXE=%~dp0..\project\x64\Release\CoverVidMaker.exe
set START_TIME=%TIME%

echo ============================================================
echo CoverVidMaker Launcher
echo ============================================================
echo.

:: Build first
call "%~dp0build.bat" --no-pause
if errorlevel 1 (
    echo [ERROR] Build failed. Aborting.
    pause
    cmd /k
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
cmd /k

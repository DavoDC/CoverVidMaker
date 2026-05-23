@echo off
:: ============================================================
:: CoverVidMaker Build Script
:: ============================================================

:: Locate MSBuild from a VS install that has the C++ tools (not just any VS)
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -find MSBuild\**\Bin\MSBuild.exe`) do set MSBUILD="%%i"
if not defined MSBUILD (
    echo [ERROR] MSBuild not found. Install Visual Studio with the C++ workload.
    if not "%1"=="--no-pause" pause
    exit /b 1
)

set SLN=%~dp0..\project\CoverVidMaker.sln
set EXE=%~dp0..\project\x64\Release\CoverVidMaker.exe
set LOG=%~dp0..\data\logs\build.log

if not exist "%~dp0..\data\logs" mkdir "%~dp0..\data\logs"

echo [BUILD] Compiling CoverVidMaker...
%MSBUILD% "%SLN%" -p:Configuration=Release -p:Platform=x64 -verbosity:minimal -m > "%LOG%" 2>&1

if errorlevel 1 (
    echo [ERROR] Build failed.
    echo.
    echo Build log:
    type "%LOG%"
    if not "%1"=="--no-pause" pause
    exit /b 1
)

echo [BUILD] Done. Exe: %EXE%
if not "%1"=="--no-pause" pause

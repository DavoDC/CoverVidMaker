@echo off
:: ============================================================
:: CoverVidMaker Build Script
:: ============================================================

setlocal enabledelayedexpansion

set MSBUILD="C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe"
set SLN=%~dp0..\project\CoverVidMaker.sln
set EXE=%~dp0..\project\x64\Release\CoverVidMaker.exe
set LOG=%~dp0..\data\logs\build.log

if not exist "%~dp0..\data\logs" mkdir "%~dp0..\data\logs"

echo [BUILD] Compiling CoverVidMaker...
%MSBUILD% "%SLN%" -p:Configuration=Release -p:Platform=x64 -verbosity:minimal > "%LOG%" 2>&1

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

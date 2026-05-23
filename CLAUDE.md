# CoverVidMaker

C++ console app that converts MP3 files to MP4 videos using album cover images as frames, via FFmpeg.

## Project Structure

- `src/` - C++ source files
- `project/` - Visual Studio solution and project files
- `scripts/` - build.bat and launch.bat (run from here)
- `docs/` - IDEAS.md, HISTORY.md, reference docs
- `media/` - working data: 1_Audio (input MP3s), 2_Covers (input PNGs), 3_Videos (output MP4s)
- `dependencies/` - FFmpeg binaries (gitignored, see dependencies/README.md)
- `data/logs/` - build logs (gitignored)

## Building and Running

Use `scripts\launch.bat` - builds then runs automatically.
Use `scripts\build.bat` to build only.

The exe must run from the repo root (launch.bat handles this via `cd /d`), since `src/Main.cpp` hardcodes relative paths to `media/` and `dependencies/`.

## Key Files

- `src/Main.cpp` - entry point, sets `mediaPath = "media/"` and `exePath = "dependencies/"`
- `src/Processor.cpp` - scans media folder, pairs audio+cover files
- `src/Generator.cpp` - calls FFmpeg to produce MP4s

## Platform

Windows only. Build with Visual Studio 2022 (v143 toolset), Release x64.

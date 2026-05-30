# CoverVidMaker - Ideas

## Consider: Rewrite in Python

Strong case for a Python rewrite (~1-2 sessions, then done):

- C++ wrapper adds zero value - FFmpeg does all media work; the wrapper is just scan + pair + subprocess
- Python unlocks: auto-download FFmpeg (FLAC_Flow pattern), pytest, no build step, consistent with 3 sibling repos
- C++ costs: Visual Studio dependency, no test framework, build step on every change, slower Claude iteration
- Rewrite would be *smaller* - the Command/MutComm abstraction classes collapse to `subprocess.run()`
- All "Future Ideas" below become easy in Python; they stay painful in C++
- David's stated preference: avoid compiled languages for home projects (build friction not worth it)

If proceeding: use FLAC_Flow as the template (deps.py for auto-download, pathlib throughout, pytest, same folder structure).

## Future Ideas

- Auto-download FFmpeg if missing - shell out to PowerShell to download from gyan.dev, extract, place in `dependencies/ffmpeg/`. Same behaviour as Python sibling repos (SBS_Download, FLAC_Flow, RivalsVidMaker). Currently opens browser + manual instructions instead.
- CLI mode: accept media folder path as argument instead of hardcoded path
- Progress bar during FFmpeg encoding
- Batch summary: total files processed, skipped, failed
- Drag-and-drop support via Windows shell extension
- Config file for output video resolution, bitrate, codec options
- Config option to force 16:9 (widescreen) output to prevent YouTube auto-classifying as a Short
  - YouTube auto-Shorts rule: <= 3 min AND vertical/square aspect ratio = forced Short, no manual override on upload
  - Fix: output in 16:9 horizontal so YouTube treats it as a regular video
  - Real case: Dolly Parton The Johnny Carson Show.mp4 was auto-converted to a Short
  - Implementation: pad/letterbox vertical source to 16:9 canvas, or add config flag `force_16x9: true`

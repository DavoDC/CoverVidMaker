# CoverVidMaker - Ideas

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

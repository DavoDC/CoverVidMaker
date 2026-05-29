# CoverVidMaker - Ideas

## FFmpeg - standardise deps structure

CVM currently places FFmpeg binaries flat in `dependencies/` directly. All Python sibling repos use `dependencies/ffmpeg/` subfolder. Standardising would mean consistent structure across repos and cleaner separation if other deps are added.

Requires C++ code changes to reference the updated binary path. Low priority unless other deps are added to `dependencies/`.

**Setup shortcut in the meantime:** copy binaries from `../ffkit/dependencies/ffmpeg/` if that repo is cloned alongside this one.

---

## Future Ideas

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

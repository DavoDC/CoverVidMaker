# CoverVidMaker - History

## 2026-05-30 - ffkit hub integration
- CoverVidMaker now auto-detects `../ffkit/dependencies/ffmpeg/` if ffkit is cloned alongside it
- Falls back to local `dependencies/ffmpeg/` subfolder (standardised from flat `dependencies/`)
- Matches the pattern used by RivalsVidMaker and SBS_Download

## 2023-06-04 - Initial release
- Original batch script version
- Rewritten in C++ for reliability and extensibility
- Supports MP3 + album art PNG -> MP4 via FFmpeg
- Handles special characters in filenames
- Handles irregular album art dimensions

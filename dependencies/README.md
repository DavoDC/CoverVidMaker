# Dependencies

## FFmpeg

CoverVidMaker auto-detects FFmpeg from [ffkit](https://github.com/DavoDC/ffkit) if cloned as a sibling repo. Otherwise it falls back to `dependencies/ffmpeg/`.

**Option 1 - ffkit hub (recommended):** Clone ffkit alongside this repo. Any ffkit tool downloads FFmpeg once into `../ffkit/dependencies/ffmpeg/`; CoverVidMaker finds it automatically. See [ffkit/README.md](https://github.com/DavoDC/ffkit) for details.

**Option 2 - standalone:** Download from https://github.com/GyanD/codexffmpeg/releases and place `ffmpeg.exe`, `ffprobe.exe`, and `ffplay.exe` in `dependencies/ffmpeg/`.

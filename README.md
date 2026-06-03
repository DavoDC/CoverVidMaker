# Cover Video Maker (CVM)

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/G2G31WKOCN)


This C++ console program converts MP3 audio files to MP4 videos by using the album cover images as frames for the video.


## Build & Run

> **Windows only.** Requires Visual Studio with C++ workload and FFmpeg binaries.

1. Place FFmpeg binaries (`ffmpeg.exe`, `ffprobe.exe`) in `dependencies/ffmpeg/`
2. Place your MP3s in `media/1_Audio/` and cover images (PNG) in `media/2_Covers/`
3. Run `scripts\launch.bat` - builds and runs automatically
4. Converted MP4s appear in `media/3_Videos/`

Alternatively, open `project/` in Visual Studio and build manually with **Ctrl+Shift+B**.

## Info
- Requires **FFmpeg** ([Official Site](https://www.ffmpeg.org/about.html), [GitHub Releases](https://github.com/GyanD/codexffmpeg/releases)) - place binaries in `dependencies/ffmpeg/`.
- Was originally a series of Batch scripts created on June 4th, 2023.
- For Windows OS only (Command class is designed for Windows).


## Features
- Highly customizable, extensible, and modular (from a developer perspective).
- Much easier to work with compared to batch scripts.
- Achieves desired results with just a single click.
- No restrictions on the number of files or video duration.
- Can handle audio filenames with special characters.
- Can handle audio files with irregular album art.


## Tech

- **Language:** C++
- **IDE:** Visual Studio (Windows only)
- **Video encoding:** [FFmpeg](https://www.ffmpeg.org/) for MP3+image → MP4 conversion

## Alternatives
- [**Online Converter**](https://www.onlineconverter.com/mp3-to-mp4): Limited to single file processing.
- [**Wondershare UniConverter**](https://videoconverter.wondershare.com/convert-mp4/mp3-to-mp4-with-image.html): Free version has many restrictions (e.g. duration limits).

## Development

**Developed:** June 2023 (originally batch scripts, rewritten in C++)

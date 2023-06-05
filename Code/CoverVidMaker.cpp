// CoverVidMaker.cpp : 
// Defines CoverVidMaker class

// Include header file
#include "CoverVidMaker.h"

// Include needed header files
#include "Command.h"

// ### Libraries
// Filesystem access
#include <filesystem>

// Namespace mods
using namespace std;
namespace fs = filesystem;

// Macro for long iterator type
#define FSIterator fs::recursive_directory_iterator

// Static Paths
string execsPath = "FFMPEG";
string ffmpegPath = execsPath + "\\ffmpeg.exe";
string ffprobePath = execsPath + "\\ffprobe.exe";
string mediaPath = "Media";
string audioPath = mediaPath + "\\1_Audio";
string coverPath = mediaPath + "\\2_Covers";
string videoPath = mediaPath + "\\3_Videos";


// Constructor
CoverVidMaker::CoverVidMaker()
{
	// Welcome message
	print("###### Welcome to CoverVidMaker! ######");

	// Step 1 - Scan audio files
	scanAudioFiles();

	// Step 2 - Get FFMPEG executables
	getFFMPEG();

	// Step 3 - Extract covers
	extractCovers();

	// Step 4 - Make videos
	makeVideos();
}


// Step 1
void CoverVidMaker::scanAudioFiles()
{
	// ### Get Audio file paths
	// For every path in the Audio folder
	for (const auto& curPath : FSIterator(audioPath)) {

		// Convert current path to string
		string curPathS = curPath.path().generic_string();

		// If it is a MP3 file
		if (contains(curPathS, ".mp3")) {

			// Add to path list
			audioFilePaths.push_back(curPathS);
		}
	}

	// ### Check Audio file paths
	// If no paths found
	if (audioFilePaths.empty())
	{
		print("\nERROR: No MP3 files present in: " + audioPath);
		print("\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		// # Else if contains at least one path
		// Get path count as string
		string pathCountS = to_string(audioFilePaths.size());

		// Notify
		print("\nMP3 Files Found: " + pathCountS);
	}
}


// Step 2
void CoverVidMaker::getFFMPEG() {

	// DO SIMPLE VERSION
	// if doestn exist
	// open URl and instruct user
	// get smallest, e.g. ffmpeg-6.0-essentials_build.7z
	// 	//	Put 'ffmpeg.exe' and 'ffprobe.exe' in the FFMPEG folder
	// 	// extract zip
	// put executables in right place
	// start https://github.com/GyanD/codexffmpeg/releases
	// if exists,  continue


	// EXAMPLE USAGE OF COMMAND CLASS
	StringV args = { "-l", "-S" };
	Command command("ls", args);
	command.runWithOutput();
}


// Step 3
void CoverVidMaker::extractCovers() {
	// TODO
	// for each audio file path (already stored)
	// -check if cover exists already, skip if so
	// -generate cover file using ffmpeg command
	// 
	// -check if created, if not, stop.
	// 
	// compare coverCount to audioFileCount?

	// 1_Covers.bat = use as model
	//REM Loop through all the MP3 files in the "Audio" folder
	//	for%% F in("%audioFolder%\*.mp3") do (
	//		REM Increment the audio file counter
	//		set / a "audioCount+=1"

	//		REM Extract the filename(without extension) of the MP3 file
	//		set "filename=%%~nF"

	//		REM Generate the output cover filename
	//		set "coverFile=%parentDir%%outputFolder%\!filename!_cover.png"

	//		REM Check if the album cover already exists
	//		if not exist "!coverFile!" (
	//			REM Use FFmpeg to extract the album cover image from the MP3 file
	//			"%scriptDir%ffmpeg.exe" -hide_banner -loglevel error -i "%%F" -an -vcodec copy -y "!coverFile!"

	//			REM Check if the cover image was generated
	//			if not exist "!coverFile!" (
	//				echo Album cover was not generated for file:%% F
	//				pause
	//				exit / b
	//				) else (
	//					set / a "coverCount+=1"
	//					)
	//				) else (
	//					echo Album cover already exists for file: !filename!.Skipping generation.
	//					set / a "coverCount+=1"
	//					)
	//				)

	//		REM Print the ending message with the count of album covers generated and the count of audio files
	//				echo Album covers generated : % coverCount% / % audioCount%
}


// Step 4
void CoverVidMaker::makeVideos() {
	// TODO
	// generate videos, check amount / total, check video lengths

	//### VIDEO STEP
	//	Use ffmpeg command from 3_Video_Track_Videos.bat for Video generation
	//	Add comment about YouTube requiring a video track for uploads
	// Get duration from ffprobe, feed to -t argument

	// Model off 3_Video_Track_Videos.bat mainly
	///*REM Loop through each video file in the OLD_VIDS folder
	//	for%% F in("OLD_VIDS\*.mp4") do (
	//		REM Get the filename without extension
	//		set "filename=%%~nF"

	//		REM Set the corresponding audio and image paths
	//		set "audio=AUDIO\!filename!.mp3"
	//		set "image=COVERS\!filename!_image.png"

	//		REM Run ffmpeg to fix the video with lower preset and adjusted bitrate
	//		ffmpeg -y -loop 1 -i "!image!" -i "!audio!" -c:v libx264 -preset slower -tune stillimage 
	// -c:a copy -pix_fmt yuv420p -b:v 1M -t 300 "FIXED_VIDS\!filename!.mp4"
	//  -hide_banner -loglevel error
}


// Helper wrapper for checking path validity
bool CoverVidMaker::isPathValid(const string& path) {
	return fs::exists(path);
}
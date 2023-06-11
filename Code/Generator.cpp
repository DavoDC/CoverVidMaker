// Generator.cpp

// Header
#include "Generator.h"

// Needed Headers
#include "Command.h"

// Namespace mods
using namespace std;


// ### Constructor
Generator::Generator(Processor& proc) : 
	ffmpegPath(proc.getFFMPEG()),
	ffprobePath(proc.getFFMPEG()),
	mediaFiles(proc.getMediaFiles())
{
	// Save file number
	fileNum = mediaFiles.getFileNum();

	// Extract covers
	extractCovers();

	// Make videos
	//makeVideos();
}



void Generator::extractCovers() {

	// Start message
	print("\nExtracting Covers...");

	// Put together common arguments
	StringV commonArgs = {
		"-hide_banner",
		"-loglevel",
		"error",
		"-i",
		"-an",
		"-vcodec",
		"copy",
		"-y"
	};

	// Iterate over all MediaFiles
	for (int i = 0; i < fileNum; i++) {

		// Create argument list using a copy of the common arguments
		StringV argList = commonArgs;

		// Insert audio input
		argList.insert(argList.begin() + 4, mediaFiles.getAudio(i));

		// Add cover output
		argList.push_back(mediaFiles.getCover(i));

		// Create command and run
		Command myCommand(ffmpegPath, argList);
		myCommand.run();
	}



	// TODO
	// for each audio file path (already stored)
	// -check if cover exists already, skip if so
	// -generate cover file using ffmpeg command
	// 
	// -check if created, if not, stop.
	// 
	// compare coverCount to audioFileCount?

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



//void Generator::makeVideos() {
//
//	// TEMP
//	print("\n### TODO: Make Videos");
//
//	// TODO
//	// generate videos, check amount / total, check video lengths
//
//	//### VIDEO STEP
//	//	Use ffmpeg command from 3_Video_Track_Videos.bat for Video generation
//	//	Add comment about YouTube requiring a video track for uploads
//	// Get duration from ffprobe, feed to -t argument
//
//	// Model off 3_Video_Track_Videos.bat mainly
//	///*REM Loop through each video file in the OLD_VIDS folder
//	//	for%% F in("OLD_VIDS\*.mp4") do (
//	//		REM Get the filename without extension
//	//		set "filename=%%~nF"
//
//	//		REM Set the corresponding audio and image paths
//	//		set "audio=AUDIO\!filename!.mp3"
//	//		set "image=COVERS\!filename!_image.png"
//
//	//		REM Run ffmpeg to fix the video with lower preset and adjusted bitrate
//	//		ffmpeg -y -loop 1 -i "!image!" -i "!audio!" -c:v libx264 -preset slower -tune stillimage 
//	// -c:a copy -pix_fmt yuv420p -b:v 1M -t 300 "FIXED_VIDS\!filename!.mp4"
//	//  -hide_banner -loglevel error
//}



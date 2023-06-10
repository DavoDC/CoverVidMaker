// CoverVidMaker.cpp

// Header
#include "CoverVidMaker.h"

// Needed Headers
#include "Command.h"

// ### Libraries
// Filesystem access
#include <filesystem>

// Namespace mods
using namespace std;
namespace fs = filesystem;

// Macro for long iterator type
#define FSIterator fs::recursive_directory_iterator


// Constructor
CoverVidMaker::CoverVidMaker(string audioPath,
	string coverPath,
	string videoPath,
	string ffmpegPath,
	string ffprobePath)
{
	// Welcome message
	print("###### Welcome to CoverVidMaker! ######");

	// Check media paths
	checkMediaPath(audioPath);
	checkMediaPath(coverPath);
	checkMediaPath(videoPath);

	// Notify
	printSuccess("Media Folders Found");

	// Check FFMPEG executables
	checkFFMPEG(ffmpegPath);
	checkFFMPEG(ffprobePath);

	// Notify
	printSuccess("FFMPEG Executables Found");

	// Save paths
	this->audioPath = audioPath;
	this->coverPath = coverPath;
	this->videoPath = videoPath;
	this->ffmpegPath = ffmpegPath;
	this->ffprobePath = ffprobePath;

	// Scan audio files
	scanAudioFiles();
}


void CoverVidMaker::checkMediaPath(string folderPath)
{
	// If media folder path is invalid
	if (!isPathValid(folderPath))
	{
		// Notify and exit
		printErr("Media folder missing: " + quoteS(folderPath), true);
	}
}


void CoverVidMaker::checkFFMPEG(string exePath) {

	// If executable does not exist
	if(!isPathValid(exePath))
	{ 
		// Notify
		printErr("FFMPEG executable missing: " + quoteS(exePath));
		
		// Open download page
		string dwlURL = "https://github.com/GyanD/codexffmpeg/releases";
		print("1) Go to this page that will open: " + dwlURL + ".");
		Command command("cmd.exe /c start", dwlURL);
		command.run();

		// Give instructions
		print("2) Download the newest, smallest archive, often the 'essentials_build.7z' one.");
		print("3) Extract the archive.");
		print("4) Ensure the executables are placed in the folder specified.");
		print("");

		// Exit
		exit(EXIT_FAILURE);
	}
}


void CoverVidMaker::scanAudioFiles()
{
	// ### Get Audio file paths
	// For every path in the Audio folder
	for (const auto& curPath : FSIterator(audioPath)) {

		// Convert current path to string
		string curPathS = curPath.path().generic_string();

		// If it is a MP3 file
		if (contains(curPathS, ".mp3")) {

			// Add to file path list
			audioFilePaths.push_back(curPathS);
		}
	}

	// ### Check Audio file paths
	// If no paths found
	if (audioFilePaths.empty())
	{
		// Notify and exit
		printErr("No MP3 files found in " + quoteS(audioPath), true);
	}
	else
	{
		// # Else if contains at least one path
		// Save file count
		fileCount = int(audioFilePaths.size());

		// Notify
		printSuccess(to_string(fileCount) + " MP3 Files Found");
	}
}


void CoverVidMaker::generateVideos()
{
	// Extract covers
	extractCovers();

	// Make videos
	//makeVideos();
}


void CoverVidMaker::extractCovers() {
	// TEMP
	print("\n### TODO: Extract Covers");


	// PROOF OF CONCEPT
	
	// Get an audio path
	string audioFP = audioFilePaths[0];

	// ### Create cover file path
	// use audio as base
	string coverFP = audioFilePaths[0];
	// change to cover folder
	replaceAll(coverFP, audioPath, coverPath);
	// change extension
	replaceAll(coverFP, ".mp3", ".png");

	// TEST
	//print("AP: " + audioPath);
	//print("AFP: " + audioFP);
	//print("CFP: " + coverFP);

	// Put together arguments
	StringV argList = {
		"-hide_banner",
		"-loglevel error",
		"-i",
		quoteD(audioFP),
		"-an",
		"-vcodec",
		"copy",
		"-y",
		quoteD(coverFP)
	};

	// Create command and run
	Command myCommand(quoteD(ffmpegPath), argList);
	myCommand.printCommand();
	myCommand.run();


	// WORKING, NEEED DOUBLE QUOTES , AND DONT USE CMD /C
	// "FFMPEG/ffmpeg.exe" -hide_banner -loglevel error -i "Media/1_Audio/Hanae - God of Gods.mp3" -an -vcodec copy -y "Media/2_Covers/Hanae - God of Gods.png"



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



void CoverVidMaker::makeVideos() {

	// TEMP
	print("\n### TODO: Make Videos");

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




bool CoverVidMaker::isPathValid(string path) {
	return fs::exists(path);
}
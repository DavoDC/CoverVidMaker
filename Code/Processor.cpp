// Processor.cpp

// Header
#include "Processor.h"

// Needed Headers
#include "Command.h"

// ### Libraries
#include <filesystem>
#include <functional>

// Namespace mods
using namespace std;
namespace fs = filesystem;

// Macro for long iterator type
#define FSIterator fs::recursive_directory_iterator


// ### Constructor

Processor::Processor(const string& mediaPath, const string& exePath)
	: 
	mediaPath(mediaPath),
	audioPath(mediaPath + "1_Audio"),
	coverPath(mediaPath + "2_Covers"),
	videoPath(mediaPath + "3_Videos"),
	exePath(exePath),
	ffmpegPath(exePath + "ffmpeg.exe"),
	ffprobePath(exePath + "ffprobe.exe")
{

	// Check folder paths and notify
	checkFolderPaths({mediaPath, audioPath, coverPath, videoPath, exePath});

	// Check executables and notify
	checkExecPaths({ffmpegPath, ffprobePath});

	//// Scan audio files
	//scanAudioFiles();
}


void Processor::checkFolderPaths(StringV folderPaths)
{
	// Define handling of missing folders
	auto folderErrorFunc = [](const string& folderPath) {
		printErr("Folder missing: " + quoteS(folderPath));
	};

	// Check folder paths
	checkPaths(folderPaths, "All Folders Found", folderErrorFunc);
}


void Processor::checkExecPaths(StringV exePaths)
{
	// Define handling of missing executables
	auto execErrorFunc = [](const string& exePath) {

		// Notify
		printErr("FFMPEG executable missing: " + quoteS(exePath));

		// Open download page
		const string dwlURL = "https://github.com/GyanD/codexffmpeg/releases";
		Command command("cmd.exe /c start", dwlURL);
		command.run();

		// Give instructions
		print("1) Go to this page that will open: " + dwlURL + ".");
		print("2) Download the newest, smallest archive (often *essentials_build.7z).");
		print("3) Extract the archive and find the 'bin' folder.");
		print("4) Copy the executables to: " + quoteS(exePath));
		print("");
	};

	// Check executable paths
	checkPaths(exePaths, "FFMPEG Executables Found", execErrorFunc);
}


void Processor::checkPaths(StringV paths, const string& successMsg, 
	function<void(const string&)> errHandler)
{
	// For all paths
	for (const string& curPath : paths) {

		// If path is not valid
		if (!isPathValid(curPath)) {

			// Call error handler
			errHandler(curPath);

			// Exit 
			exit(EXIT_FAILURE);
		}
	}

	// If didn't exit, was successful:
	printSuccess(successMsg);
}



void Processor::scanAudioFiles()
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
		fileNum = int(audioFilePaths.size());

		// Notify
		printSuccess(to_string(fileNum) + " MP3 Files Found");
	}
}



bool Processor::isPathValid(string path) {
	return fs::exists(path);
}
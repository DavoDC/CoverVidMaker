// Processor.cpp

// Header
#include "Processor.h"

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


// ### Constructor

Processor::Processor(const std::string& mediaPath, const std::string& execsPath)
	: 
	mediaPath(mediaPath),
	audioPath(mediaPath + "1_Audio"),
	coverPath(mediaPath + "2_Covers"),
	videoPath(mediaPath + "3_Videos"),
	execsPath(execsPath),
	ffmpegPath(execsPath + "ffmpeg.exe"),
	ffprobePath(execsPath + "ffprobe.exe")
{

	// Check folder paths and notify
	checkFolderPaths({mediaPath, audioPath, coverPath, videoPath, execsPath});
	printSuccess("All Folders Found");

	//// Check FFMPEG executables and notify
	//checkFFMPEG(ffmpegPath);
	//checkFFMPEG(ffprobePath);
	//printSuccess("FFMPEG Executables Found");

	//// Scan audio files
	//scanAudioFiles();
}


void Processor::checkFolderPaths(StringV folderPaths)
{
	// For all folder paths
	for (const std::string& curFP : folderPaths) {

		// If path invalid
		if (!isPathValid(curFP))
		{
			// Notify and exit
			printErr("Folder missing: " + quoteS(curFP), true);
		}
	} 
}


void Processor::checkFFMPEG(string exePath) {

	// If executable does not exist
	if (!isPathValid(exePath))
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
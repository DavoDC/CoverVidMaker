// Processor.cpp

// Header
#include "Processor.h"

// Needed Headers
#include "Command.h"

// ### Libraries
#include <functional>

// Namespace mods
using namespace std;


// ### Constructor

Processor::Processor(const string& mediaPath, const string& exePath) :
	mediaPath(mediaPath),
	audioPath(mediaPath + "1_Audio"),
	coverPath(mediaPath + "2_Covers"),
	videoPath(mediaPath + "3_Videos"),
	exePath(exePath),
	ffmpegPath(exePath + "ffmpeg.exe"),
	ffprobePath(exePath + "ffprobe.exe")
{
	// Media file paths
	StringV mediaFilePaths = { audioPath, coverPath, videoPath };

	// Check folder paths and notify
	StringV folderPaths(mediaFilePaths.begin(), mediaFilePaths.end());
	folderPaths.insert(folderPaths.begin(), { mediaPath, exePath });
	checkFolderPaths(folderPaths);

	// Check executables and notify
	checkExecPaths({ ffmpegPath, ffprobePath });

	// Scan audio files
	mediaFileList = MediaFileList(mediaFilePaths);
}


std::string Processor::getFFMPEG() const
{
	return quoteD(ffmpegPath);
}


std::string Processor::getFFPROBE() const
{
	return quoteD(ffprobePath);
}


MediaFileList& Processor::getMediaFiles()
{
	return mediaFileList;
}



void Processor::checkFolderPaths(const StringV& folderPaths)
{
	// Define handling of missing folders
	auto folderErrorFunc = [](const string& folderPath) {
		printErr("Folder missing: " + quoteS(folderPath));
	};

	// Check folder paths
	checkPaths(folderPaths, "All Folders Found", folderErrorFunc);
}


void Processor::checkExecPaths(const StringV& exePaths)
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


void Processor::checkPaths(const StringV& paths, const string& successMsg,
	const function<void(const string&)>& errHandler)
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
// Processor.cpp

// Header
#include "Processor.h"

// Needed Headers
#include "Command.h"

// File Path Sanitization Libraries
#include <windows.h>
#include <codecvt>
#include <locale>
#include <cctype>

// Namespace mods
using namespace std;


// ### Constructor

Processor::Processor(const string& mediaPath, const string& exePath) :
	mediaFolder(mediaPath),
	audioFolder(mediaPath + "1_Audio"),
	coverFolder(mediaPath + "2_Covers"),
	videoFolder(mediaPath + "3_Videos"),
	exeFolder(exePath),
	ffmpegFile(exePath + "ffmpeg.exe"),
	ffprobeFile(exePath + "ffprobe.exe")
{
	// Media file paths
	StringV mediaFilePaths = { audioFolder, coverFolder, videoFolder };

	// Check folder paths and notify
	StringV folderPaths(mediaFilePaths.begin(), mediaFilePaths.end());
	folderPaths.insert(folderPaths.begin(), { mediaPath, exePath });
	checkFolderPaths(folderPaths);

	// Check executables and notify
	checkExecPaths({ ffmpegFile, ffprobeFile });

	// Construct MediaFileList from audio files
	mediaFileList = MediaFileList(mediaFilePaths, getFFPROBEexe());
}


string Processor::getFFMPEGexe() const
{
	return quoteD(ffmpegFile);
}


string Processor::getFFPROBEexe() const
{
	return quoteD(ffprobeFile);
}


MediaFileList& Processor::getMediaFiles()
{
	return mediaFileList;
}



void Processor::checkFolderPaths(const StringV& folderPaths)
{
	// Define handling of missing folders
	auto folderErrorFunc = [](const string& folderPath) {
		printErr("Folder missing: " + quoteS(folderPath), true);
	};

	// Check folder paths
	checkPaths(folderPaths, "All Folders Found", folderErrorFunc);
}


void Processor::checkExecPaths(const StringV& exePaths)
{
	// Define handling of missing executables
	auto execErrorFunc = [](const string& exePath) {

		// Notify
		printErr("FFMPEG executable missing: " + quoteS(exePath), true);

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
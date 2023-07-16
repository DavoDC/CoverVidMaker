// Processor.cpp

// Header
#include "Processor.h"

// Needed Headers
#include "Command.h"

// ### Libraries
#include <functional>
#include <filesystem>

// File Path Sanitization Libraries
#include <Windows.h>
#include <codecvt>
#include <locale>
#include <cctype>

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

	// Sanitize audio files and scan
	sanitiseAudioFileNames(audioPath);
	mediaFileList = MediaFileList(mediaFilePaths, getFFPROBE());
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


void Processor::sanitiseAudioFileNames(const string audioFolder)
{
	// For every audio file path
	for (const auto& curPath : filesystem::directory_iterator(audioFolder)) {
		if (curPath.path().extension() == L".mp3") {

			// Sanitize path
			wstring curFilename = curPath.path().filename();
			int bufferSize = WideCharToMultiByte(CP_UTF8, 0, curFilename.c_str(), 
				-1, nullptr, 0, nullptr, nullptr);
			string sanitizedFilename(bufferSize, '\0');
			WideCharToMultiByte(CP_UTF8, 0, curFilename.c_str(), -1, 
				&sanitizedFilename[0], bufferSize, nullptr, nullptr);

			// Replace " - " with " "
			size_t startPos = 0;
			while ((startPos = sanitizedFilename.find(" - ", startPos)) != string::npos) {
				sanitizedFilename.replace(startPos, 3, " ");
				startPos += 1; // Move past the replaced space
			}

			// Remove any characters other than alphanumeric, space, and dot
			sanitizedFilename.erase(remove_if(sanitizedFilename.begin(), sanitizedFilename.end(), 
				[](char c) {
				return !(isalnum(c) || c == ' ' || c == '.');
				}), sanitizedFilename.end());

			// Rename file
			int wideBufferSize = MultiByteToWideChar(CP_UTF8, 0, 
				sanitizedFilename.c_str(), -1, nullptr, 0);
			wstring finalFilename(wideBufferSize, L'\0');
			MultiByteToWideChar(CP_UTF8, 0, sanitizedFilename.c_str(), -1, 
				&finalFilename[0], wideBufferSize);
			filesystem::rename(curPath.path(), curPath.path().parent_path() / finalFilename);
		}
	}
}
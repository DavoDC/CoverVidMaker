// CoverVidMaker.cpp : 
// Defines CoverVidMaker class

// Include header file
#include "CoverVidMaker.h"

// Include needed header files
#include "CommandExecutor.h"

// ### Libraries
// Filesystem access
#include <filesystem>

// Namespace mods
using namespace std;
namespace fs = filesystem;

// Macro for long iterator type
#define FSIterator fs::recursive_directory_iterator

// Folder Paths
string execsPath = "FFMPEG";
string mediaPath = "Media";
string audioPath = mediaPath + "\\1_Audio";
string coverPath = mediaPath + "\\2_Covers";
string videoPath = mediaPath + "\\3_Videos";


// Constructor
CoverVidMaker::CoverVidMaker()
{
	// Welcome message
	print("\n###### Welcome to CoverVidMaker! ######");

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

	// TODO
	//1) get executables - wget on github release, like JavaYTD
	//2) generate covers, check amount / total
	//3) generate videos, check amount / total
	//4) check video lengths ? ?


	// PROOF OF CONCEPT
	print("\n\n");
	CommandExecutor executor;
	wstring command = L"ping";
	vector<wstring> arguments = { L"www.example.com" };
	executor.Execute(command, arguments);
}


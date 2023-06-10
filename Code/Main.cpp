// Main.cpp : 
// This file contains the 'main' function. 
// Program execution begins and ends there.

// ### Libraries

// No header file for self

// Include needed headers
#include "Common.h"
#include "CoverVidMaker.h"

// Namespace mods
using namespace std;

// Main Folder Paths
string mediaPath = "Media\\";
string execsPath = "FFMPEG\\";


// Main function
int main()
{
	// Get derived folder paths
	string audioPath = mediaPath + "1_Audio";
	string coverPath = mediaPath + "2_Covers";
	string videoPath = mediaPath + "3_Videos";
	string ffmpegPath = execsPath + "ffmpeg.exe";
	string ffprobePath = execsPath + "ffprobe.exe";

	// Initialize CVM
	CoverVidMaker cvm(audioPath, coverPath, videoPath, ffmpegPath, ffprobePath);

	// Generate videos
	cvm.generateVideos();

	// END
	print("\n");
}

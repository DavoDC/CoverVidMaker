// Main.cpp

// Header
// NONE

// Needed Headers
#include "Common.h"
#include "CoverVidMaker.h"

// Namespace mods
using namespace std;

// Main Folder Paths
string mediaPath = "Media/";
string execsPath = "FFMPEG/";


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

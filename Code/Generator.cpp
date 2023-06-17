// Generator.cpp

// Header
#include "Generator.h"

// Needed Headers
// None

// Namespace mods
using namespace std;


// ### Constructor
Generator::Generator(Processor& proc) :
	ffmpegPath(proc.getFFMPEG()),
	ffprobePath(proc.getFFMPEG()),
	mediaFiles(proc.getMediaFiles()),
	fileNum(mediaFiles.getFileNum())
{
	// Initialize cover command
	StringV coverCommArgs = {
		"-hide_banner",
		"-loglevel",
		"error",
		"-i",
		Command::getMutArg("INPUT_AUDIO"),
		"-an",
		"-vcodec",
		"copy",
		"-y",
		Command::getMutArg("OUTPUT_COVER")
	};
	coverComm = Command(ffmpegPath, coverCommArgs);

	// Extract covers
	extractCovers();

	// Make videos
	//makeVideos();
}



void Generator::extractCovers() {

	// Start message
	print("\nExtracting Covers...");

	// Cover count
	int coverCount = 0;

	// For all audio files
	for (int i = 0; i < fileNum; i++) {

		// Extract cover path
		string coverPath = mediaFiles.getCover(i);

		// If cover already made
		if (isPathValid(coverPath)) {

			// Add to count and skip
			coverCount++;
			continue;
		}
		else {
			// Else, if cover doesn't exist, generate it
			coverComm.updateArg("INPUT_AUDIO", mediaFiles.getAudio(i));
			coverComm.updateArg("OUTPUT_COVER", coverPath);
			coverComm.run();

			// If cover was successfully generated
			if (isPathValid(coverPath)) {

				// Add to count
				coverCount++;
			}
			else {
				// Else if didn't generate, notify
				printErr("Failed to generate cover: " + coverPath + " ");
			}
		}
	}

	// Print summary message
	string coverNumS = to_string(coverCount);
	string fileNumS = to_string(fileNum);
	print(format("Finished. Covers generated: {}/{} !", coverNumS, fileNumS));
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



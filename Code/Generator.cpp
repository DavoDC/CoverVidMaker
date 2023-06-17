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
		"-loglevel error",
		"-i",
		Command::getMutArg("INPUT_AUDIO"),
		"-an",
		"-vcodec copy",
		"-y",
		Command::getMutArg("OUTPUT_COVER")
	};
	coverComm = Command(ffmpegPath, coverCommArgs);

	// Extract covers
	extractCovers();

	// Initialize video command
	StringV vidCommArgs = {
		"-hide_banner",
		"-loglevel error",
		"-loop 1",
		"-i",
		Command::getMutArg("INPUT_COVER"),
		"-i",
		Command::getMutArg("INPUT_AUDIO"),
		"-c:v libx264",
		"-preset slower",
		"-tune stillimage",
		"-c:a copy",
		"-pix_fmt yuv420p",
		"-b:v 1M",
		"-t",
		Command::getMutArg("INPUT_DURATION"),
		"-y",
		Command::getMutArg("OUTPUT_VIDEO")
	};
	vidComm = Command(ffmpegPath, vidCommArgs);

	// Make videos
	makeVideos();
}



void Generator::extractCovers() {

	// Start message
	print("\n### Extracting Covers...");

	// Cover count
	int coverCount = 0;

	// For all audio files
	for (int i = 0; i < fileNum; i++) {

		// Extract cover path
		string coverPath = mediaFiles.getCover(i);

		// If cover already made
		if (isPathValid(coverPath)) {

			// Add to count
			coverCount++;

			// Notify
			printUpdate(coverCount);

			// Skip
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

	// Print finish message
	print("\nFinished!");
	printUpdate(coverCount);
}



void Generator::makeVideos() {

	// Start message
	print("\n### Making Videos...");

	// Video count
	int vidCount = 0;

	// For all audio files
	for (int i = 0; i < fileNum; i++) {

		// Extract video path
		string videoPath = mediaFiles.getVideo(i);

		// If video already made
		if (isPathValid(videoPath)) {

			// Add to count
			vidCount++;

			// Notify
			printUpdate(vidCount);

			// Skip
			continue;
		}
		else {
			// Else, if video doesn't exist, generate it
			vidComm.updateArg("INPUT_COVER", mediaFiles.getCover(i));
			vidComm.updateArg("INPUT_AUDIO", mediaFiles.getAudio(i));
			vidComm.updateArg("INPUT_DURATION", "5");
			vidComm.updateArg("OUTPUT_VIDEO", videoPath);
			vidComm.run();

			// If video was successfully generated
			if (isPathValid(videoPath)) {

				// Add to count
				vidCount++;

				// Notify
				printUpdate(vidCount);
			}
			else {
				// Else if didn't generate, notify
				printErr("Failed to generate video: " + videoPath + " ");
			}
		}
	}

	// Print finish message
	print("\nFinished!");
	printUpdate(vidCount);
}

void Generator::printUpdate(int filesGenerated)
{
	string fileGenS = to_string(filesGenerated);
	string fileNumS = to_string(fileNum);
	print(format("Generated: {}/{} !", fileGenS, fileNumS));
}



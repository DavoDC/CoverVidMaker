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
	ffprobePath(proc.getFFPROBE()),
	mediaFiles(proc.getMediaFiles()),
	fileNum(mediaFiles.getFileNum())
{
	// Initialize cover command
	StringV coverCommArgs = {
		"-hide_banner",
		"-loglevel error",
		"-i", Command::getMutArg(INPUT_AUDIO),
		"-an",
		"-vcodec copy",
		"-y", Command::getMutArg(OUTPUT_COVER)
	};
	coverComm = Command(ffmpegPath, coverCommArgs);

	// Extract covers
	extractCovers();

	// Initialize duration command
	StringV durCommArgs = {
		"-v quiet -print_format",
		"compact=print_section=0:nokey=1:escape=csv -show_entries",
		"format=duration", Command::getMutArg(INPUT_AUDIO)
	};
	durComm = Command(ffprobePath, durCommArgs);

	// Initialize video command
	StringV vidCommArgs = {
		"-hide_banner",
		"-loglevel error",
		"-loop 1",
		"-i", Command::getMutArg(INPUT_COVER),
		"-i", Command::getMutArg(INPUT_AUDIO),
		"-c:v libx264",
		"-preset fast",
		"-tune stillimage",
		"-c:a copy",
		"-pix_fmt yuv420p",
		"-b:v 1M",
		"-t", Command::getMutArg(INPUT_DURATION),
		"-y", Command::getMutArg(OUTPUT_VIDEO)
	};
	vidComm = Command(ffmpegPath, vidCommArgs);

	// Make videos
	makeVideos();
}


void Generator::extractCovers() {
	generateMedia("Extracting Covers",
		[this](int i) { return mediaFiles.getCover(i); },
		[this](int i) {
			coverComm.updateArg(INPUT_AUDIO, mediaFiles.getAudio(i));
			coverComm.updateArg(OUTPUT_COVER, mediaFiles.getCover(i));
			coverComm.run();
			return coverComm.getTimeTaken();
		});
}


void Generator::makeVideos() {
	generateMedia("Making Videos",
		[this](int i) { return mediaFiles.getVideo(i); },
		[this](int i) {

			// Update audio file paths
			string audioFP = mediaFiles.getAudio(i);
			vidComm.updateArg(INPUT_AUDIO, audioFP);
			durComm.updateArg(INPUT_AUDIO, audioFP);

			// Get and update duration
			durComm.run();
			double rawDur = stod(durComm.getOutput()) + 2;
			string duration = to_string(static_cast<int>(round(rawDur)));
			vidComm.updateArg(INPUT_DURATION, duration);

			// Update normal args
			vidComm.updateArg(INPUT_COVER, mediaFiles.getCover(i));
			vidComm.updateArg(OUTPUT_VIDEO, mediaFiles.getVideo(i));

			// Run and return time taken
			vidComm.run();
			return vidComm.getTimeTaken();
		});
}

void Generator::generateMedia(const string& actionDesc,
	PathGetter getOutputPath, GenComm runGenComm) {

	// Start message
	print("\n### " + actionDesc + "...");

	// Count
	int count = 0;

	// For all media files
	for (int i = 0; i < fileNum; i++) {

		// Get media file path
		string outputFilePath = getOutputPath(i);

		// If file already exists
		if (isPathValid(outputFilePath)) {

			// Increment count and notify
			printUpdate(++count, 0);

			// Skip
			continue;
		}

		// Generate the file and save time taken
		double timeTaken = runGenComm(i);

		// If the file was successfully generated
		if (isPathValid(outputFilePath)) {

			// Increment count and notify
			printUpdate(++count, timeTaken);
		}
		else {
			// Notify if generation failed
			printErr("Failed to generate: " + outputFilePath);
		}
	}
}


void Generator::printUpdate(const int curFileNum, const double timeTaken) {

	// Update string holder
	string update = "";

	// Get current files over total
	string fileGenS = to_string(curFileNum);
	string fileNumS = to_string(fileNum);
	update += format("Generated: {}/{}!", fileGenS, fileNumS);

	// Add second part
	string timePart = "";
	if (timeTaken == 0) {
		timePart += "Previously";
	} else {
		timePart += Command::getTimeTaken(timeTaken);
	}
	update += format(" ({})", timePart);

	// Print final result
	print(update);
}
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
	mediaFiles(proc.getMediaFiles()),
	fileNum(mediaFiles.getFileNum())
{
	// Print total duration
	print(format("\nTotal Duration: {}", mediaFiles.getTotalDuration()));

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
			vidComm.updateArg(INPUT_AUDIO, mediaFiles.getAudio(i));
			vidComm.updateArg(INPUT_DURATION, mediaFiles.getDuration(i));
			vidComm.updateArg(INPUT_COVER, mediaFiles.getCover(i));
			vidComm.updateArg(OUTPUT_VIDEO, mediaFiles.getVideo(i));
			vidComm.run();
			return vidComm.getTimeTaken();
		});
}

void Generator::generateMedia(const string& actionDesc,
	PathGetter getOutputPath, GenComm runGenComm) {

	// Print starting message
	print(format("\n### {} ({})...", actionDesc, to_string(fileNum)));

	// Count
	int count = 0;

	// Total time taken
	double totalTimeTaken = 0;

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

		// Generate the file and save and accumulate time taken
		double timeTaken = runGenComm(i);
		totalTimeTaken += timeTaken;

		// If the file was successfully generated
		if (isPathValid(outputFilePath)) {

			// Increment count and notify
			printUpdate(++count, timeTaken);
		} else {
			// Notify if generation failed
			printErr("Failed to generate: " + outputFilePath);
		}
	}

	// # Print ending message
	// Only print overall message if more than one file involved
	if (fileNum > 1) {

		// If generation was instant
		if (totalTimeTaken == 0) {

			// Files must have generated before
			print("All files were generated previously!");
		} else {

			// Else if took time, print total time taken
			print(format("Total {}", Command::formatTimeTaken(totalTimeTaken)));
		}
	}
}


void Generator::printUpdate(const int curFileNum, const double timeTaken) {

	// Update holder
	string update = "";

	// Add current files over total
	string fileGenS = to_string(curFileNum);
	string fileNumS = to_string(fileNum);
	update += format("Generated: {}/{}!", fileGenS, fileNumS);

	// Time part holder
	string timePart = "";

    // Set time part
	if (timeTaken == 0) {
		timePart += "Previously";
	} else {
		timePart += Command::formatTimeTaken(timeTaken);
	}

    // Add time part
	update += format(" ({})", timePart);

	// Result
	print(update);
}
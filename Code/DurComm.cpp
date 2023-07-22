// DurComm.cpp

// Header
#include "DurComm.h"

// Namespace mods
using namespace std;


// ### Constructor

DurComm::DurComm(const std::string& ffprobePath)
{
	// Check FFPROBE path
	if (!contains(ffprobePath, "ffprobe.exe")) {
		// If path doesn't contain correct EXE, notify and exit
		printErr("Duration Command needs 'ffprobe.exe' path but was given " + quoteS(ffprobePath), true);
	}

	// Setup argument list
	StringV durCommArgs = {
		"-v quiet -print_format",
		"compact=print_section=0:nokey=1:escape=csv -show_entries",
		"format=duration", Command::getMutArg(INPUT_AUDIO)
	};

	// Initialize underlying command
	durationCommand = Command(ffprobePath, durCommArgs);
}

// ### Public methods

Seconds DurComm::getDuration(const std::string audioFilePath)
{
	// Update audio path
	durationCommand.updateArg(INPUT_AUDIO, quoteD(audioFilePath));

	// Run command
	durationCommand.run();

	// Extract numerical duration from output
	double rawDur = stod(durationCommand.getOutput()) + 2;
	return static_cast<int>(round(rawDur));
}
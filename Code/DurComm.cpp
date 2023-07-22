// DurComm.cpp

// Header
#include "DurComm.h"

// Namespace mods
using namespace std;

// ### Constructor

DurComm::DurComm(const string& ffprobePath)
{
	// If program name doesn't contain FFPROBE executable, notify and exit
	if (!contains(ffprobePath, "ffprobe.exe")) {
		string msg = "DurComm needs 'ffprobe.exe' but was given ";
		printErr(msg + quoteS(ffprobePath), true);
	}

	// Setup argument list
	StringV durCommArgs = {
		"-v quiet -print_format",
		"compact=print_section=0:nokey=1:escape=csv -show_entries",
		"format=duration", MutComm::getMutArg(INPUT_AUDIO)
	};

	// Initialize underlying command
	command = MutComm(ffprobePath, durCommArgs);
}

// ### Public methods

Seconds DurComm::getDuration(const string& audioFilePath)
{
	// Update audio path
	command.updateMutArg(INPUT_AUDIO, quoteD(audioFilePath));

	// Run command
	command.run();

	// Extract numerical duration from output
	double rawDur = stod(command.getOutput()) + 2;
	return static_cast<int>(round(rawDur));
}
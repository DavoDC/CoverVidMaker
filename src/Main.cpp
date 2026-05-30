// Main.cpp

// Header
// NONE

// Needed Headers
#include "Common.h"
#include "Processor.h"
#include "Generator.h"

// Namespace mods
using namespace std;

// Media folder path
string mediaPath = "media/";


int main()
{

	// Welcome message
	print("###### Welcome to CoverVidMaker! ######");

	// Use ffkit shared FFmpeg hub if sibling repo is present, otherwise use local subfolder
	const string ffkitPath = "../ffkit/dependencies/ffmpeg/";
	const string localPath = "dependencies/ffmpeg/";
	string exePath = fs::exists(ffkitPath) ? ffkitPath : localPath;

	// Process files
	Processor proc(mediaPath, exePath);

	// Generate files
	Generator gen(proc);

	// END
	print("");
}

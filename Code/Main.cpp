// Main.cpp

// Header
// NONE

// Needed Headers
#include "Common.h"
#include "Processor.h"
#include "Generator.h"

// Namespace mods
using namespace std;

// Main Folder Paths
string mediaPath = "Media/";
string exePath = "FFMPEG/";


int main()
{
	
	// Welcome message
	print("###### Welcome to CoverVidMaker! ######");

	// Process files
	Processor proc(mediaPath, exePath);
	
	// Generate files
	Generator gen(proc);

	// END
	print("\n");
}

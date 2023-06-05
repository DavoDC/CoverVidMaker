#pragma once

// CoverVidMaker.h
// Converts MP3 audio files to MP4 videos using album covers

// ### Headers
// Include common
#include "Common.h"

// Include needed headers
//#include "MatchList.h"


// ### Libraries
// For set
//#include <set>


// ### Macros
// String set type
//#define StringSet std::set<std::string>



// Declare CoverVidMaker class
class CoverVidMaker {

public:

	// Constructor
	CoverVidMaker();

	
private:
	// ### Private fields
	// Audio file paths list
	StringV audioFilePaths;
	

	// ### Private methods
	//std::string getReplayPath();
};


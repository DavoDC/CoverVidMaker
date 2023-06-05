#pragma once

// CoverVidMaker.h
// Converts MP3 audio files to MP4 videos using album covers

// ### Headers
// Include common
#include "Common.h"

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
	// Main Steps
	void scanAudioFiles();
	void getFFMPEG();
	void extractCovers();
	void makeVideos();

	// Other
	bool isPathValid(const std::string&);
};


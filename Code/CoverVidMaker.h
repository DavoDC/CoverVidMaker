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
	CoverVidMaker(std::string audioPath, 
		std::string coverPath,
		std::string videoPath,
		std::string ffmpegPath, 
		std::string ffprobePath);

	// ### Public methods
	void generateVideos();
	
private:
	// ### Private fields
	// Audio file paths list
	StringV audioFilePaths;

	// File count
	int fileCount;
	
	// ### Private methods
	// ## Main Steps
	// # Initialization
	void checkMediaPath(std::string folderPath);
	void checkFFMPEG(std::string exePath);
	void scanAudioFiles(std::string audioPath);
	// # Generation
	void extractCovers();
	void makeVideos();

	// Helpers
	void printSuccess(std::string msg);
	void printErr(std::string msg, bool exitAfter=false);
	bool isPathValid(std::string);
	std::string quote(std::string s);
};


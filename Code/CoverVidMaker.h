#pragma once

// CoverVidMaker.h

// ### Headers
// Include common
#include "Common.h"

/**
 * @brief Converts MP3 audio files to MP4 videos using album covers
*/
class CoverVidMaker {

public:

	// ### Constructor
	
	/**
	 * @brief Construct CVM
	 * @param audioPath Path to audio files (MP3s)
	 * @param coverPath Path to album cover files (PNGs)
	 * @param videoPath Path to video files (MP4s)
	 * @param ffmpegPath Path to ffmpeg.exe
	 * @param ffprobePath Path to ffprobe.exe
	*/
	CoverVidMaker(std::string audioPath, 
		std::string coverPath,
		std::string videoPath,
		std::string ffmpegPath, 
		std::string ffprobePath);

	// ### Public methods

	/**
	 * @brief Generate videos from audio and covers
	*/
	void generateVideos();
	
private:
	// ### Private fields

	// Paths
	std::string audioPath;
	std::string coverPath;
	std::string videoPath;
	std::string ffmpegPath;
	std::string ffprobePath;
	
	/**
	 * @brief Audio file paths list
	*/
	StringV audioFilePaths;

	/**
	 * @brief File count
	*/
	int fileCount;
	

	// ### Private methods

	// # Initialization

	/**
	 * @brief Check a given media folder path
	*/
	void checkMediaPath(std::string folderPath);

	/**
	 * @brief Check a given FFMPEG executable
	 * @param exePath Path to the .exe
	*/
	void checkFFMPEG(std::string exePath);

	/**
	 * @brief Scan audio files
	*/
	void scanAudioFiles();

	// # Generation

	/**
	 * @brief Extract album covers
	*/
	void extractCovers();

	/**
	 * @brief Make videos
	*/
	void makeVideos();


	// # Helpers

	/**
	 * @return True if the given path is valid.
	*/
	bool isPathValid(std::string);
};


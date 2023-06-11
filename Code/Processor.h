#pragma once

// Processor.h

// ### Headers
// Include common
#include "Common.h"

/**
 * @brief Check, processes and handles files
*/
class Processor {
public:
    // ### Constructor

    /**
     * @param mediaPath Media folder path
     * @param execsPath Executable folder path
    */
    Processor(const std::string& mediaPath, const std::string& execsPath);

private:
	// ### Private fields

	/**
	 * @brief Media folder path
	*/
	const std::string mediaPath;

	/**
	 * @brief Audio files (MP3s) folder path
	*/
	const std::string audioPath;

	/**
	 * @brief Album cover files (PNGs) folder path
	*/
	const std::string coverPath;

	/**
	 * @brief Video files (MP4s) folder path
	*/
	const std::string videoPath;

	/**
	 * @brief Executable folder path
	*/
	const std::string execsPath;

	/**
	 * @brief ffmpeg.exe file path
	*/
	const std::string ffmpegPath;

	/**
	 * @brief ffprobe.exe file path
	*/
	const std::string ffprobePath;


	/**
	 * @brief Audio file paths list
	*/
	StringV audioFilePaths;

	/**
	 * @brief Number of media files
	*/
	int fileNum;


	// ### Private methods

	// # Initialization

	/**
	 * @brief Check folder paths
	*/
	void checkFolderPaths(StringV folderPaths);

	/**
	 * @brief Check a given FFMPEG executable
	 * @param exePath Path to the .exe
	*/
	void checkFFMPEG(std::string exePath);

	/**
	 * @brief Scan audio files
	*/
	void scanAudioFiles();

	/**
	 * @return True if the given path is valid.
	*/
	bool isPathValid(std::string);
};
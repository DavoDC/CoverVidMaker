#pragma once

// Processor.h

// ### Headers
// Include common
#include "Common.h"

// Include needed headers
#include <functional>

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
	const std::string exePath;

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
	 * @brief Check executable paths
	*/
	void checkExecPaths(StringV execPaths);

	/**
	 * @brief Check a given list of paths, handling success and errors in a given way.
	 * @param paths The list of paths.
	 * @param successMsg Message printed upon success.
	 * @param errHandler Error handler function
	*/
	void checkPaths(StringV paths, const std::string& successMsg,
		std::function<void(const std::string&)> errHandler);

	/**
	 * @brief Scan audio files
	*/
	void scanAudioFiles();

	/**
	 * @return True if the given path is valid.
	*/
	bool isPathValid(std::string);
};
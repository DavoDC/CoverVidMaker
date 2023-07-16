#pragma once

// Processor.h

// ### Headers
// Include common
#include "Common.h"

// Include needed headers
#include "MediaFileList.h"


/**
 * @brief Processes input files and folders
*/
class Processor {
public:
    // ### Constructor

    /**
     * @param mediaPath Media folder path
     * @param execsPath Executable folder path
    */
    Processor(const std::string& mediaPath, const std::string& execsPath);


	// ### Public methods

	/**
	 * @return ffmpeg.exe file path
	*/
	std::string getFFMPEG() const;

	/**
	 * @return ffprobe.exe file path
	*/
	std::string getFFPROBE() const;

	/**
	 * @return Media file list
	*/
	MediaFileList& getMediaFiles();


private:
	// ### Private fields



	// # Media Paths

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




	// # Executable Paths

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
	 * @brief Media file list
	*/
	MediaFileList mediaFileList;




	// ### Private methods

	/**
	 * @brief Check folder paths
	 * @param folderPaths The list of folder paths to check
	*/
	void checkFolderPaths(const StringV& folderPaths);

	/**
	 * @brief Check executable paths
	 * @param execPaths The list of executable paths to check
	*/
	void checkExecPaths(const StringV& execPaths);

	/**
	 * @brief Check a given list of paths, handling success and errors in a given way.
	 * @param paths The list of paths.
	 * @param successMsg Message printed upon success.
	 * @param errHandler Error handler function
	*/
	void checkPaths(const StringV& paths, const std::string& successMsg,
		const std::function<void(const std::string&)>& errHandler);

	/**
	 * @brief Sanitize audio file names by renaming them
	 * @param audioPath The audio folder path
	*/
	void sanitiseAudioFileNames(const std::string& audioFolder);

};
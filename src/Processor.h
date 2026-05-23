#pragma once

// Processor.h

// ### Headers
#include "Common.h"
#include "MediaFileList.h"

/**
 * @brief Processes input files and folders
*/
class Processor {
public:
    // ### Constructor

    /**
     * @param mediaFolder Media folder path
     * @param exeFolder Executable folder path
    */
    Processor(const std::string& mediaFolder, const std::string& exeFolder);

	// ### Public methods

	/**
	 * @return ffmpeg.exe file path
	*/
	std::string getFFMPEGexe() const;

	/**
	 * @return ffprobe.exe file path
	*/
	std::string getFFPROBEexe() const;

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
	const std::string mediaFolder;

	/**
	 * @brief Audio files (MP3s) folder path
	*/
	const std::string audioFolder;

	/**
	 * @brief Album cover files (PNGs) folder path
	*/
	const std::string coverFolder;

	/**
	 * @brief Video files (MP4s) folder path
	*/
	const std::string videoFolder;

	// # Executable Paths

	/**
	 * @brief Executable folder path
	*/
	const std::string exeFolder;

	/**
	 * @brief ffmpeg.exe file path
	*/
	const std::string ffmpegFile;

	/**
	 * @brief ffprobe.exe file path
	*/
	const std::string ffprobeFile;

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
	 * @brief Check executable files
	 * @param execPaths The list of executable file paths
	*/
	void checkExecPaths(const StringV& exeFilePaths);

	/**
	 * @brief Check a given list of paths, handling success and errors in a given way.
	 * @param paths The list of paths.
	 * @param successMsg Message printed upon success.
	 * @param errHandler Error handler function
	*/
	void checkPaths(const StringV& paths, const std::string& successMsg,
		const std::function<void(const std::string&)>& errHandler);
};
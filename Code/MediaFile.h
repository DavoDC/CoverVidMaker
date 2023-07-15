#pragma once

// MediaFile.h

// ### Headers
// Include common
#include "Common.h"

/**
 * @brief Represents a media file
*/
class MediaFile {
public:
    // ### Constructor
    MediaFile(const std::string& audioFilePath, StringV mediaFilePaths, 
		Seconds duration);

	// ### Public methods

	/**
	 * @return Audio file path
	*/
	const std::string getAFP() const;

	/**
	 * @return Cover file path
	*/
	const std::string getCFP() const;

	/**
	 * @return Video file path
	*/
	const std::string getVFP() const;

	/**
	 * @brief Get the duration of the audio file.
	*/
	const std::string getDuration() const;

private:
    // ### Private fields

	/**
	 * @brief Audio file (MP3) path
	*/
	const std::string audioFilePath;

	/**
	 * @brief Album cover file (PNG) path
	*/
	std::string coverFilePath;

	/**
	 * @brief Video file (MP4) path
	*/
	std::string videoFilePath;

	/**
	 * @brief Duration of the audio file.
	*/
	const Seconds duration;


    // ### Private methods

	/**
	 * @brief Transform one media file path into another
	 * @param filePath The original file path.
	 * @param oldFolder The old media folder.
	 * @param newFolderPath The new media folder.
	 * @param newExt The new extension.
	 * @param oldExt The old extension (Default: '.mp3').
	 * @return 
	*/
	std::string getMediaFilePath(const std::string& filePath,
		const std::string& oldFolder, const std::string& newFolder,
		const std::string& newExt, const std::string& oldExt = ".mp3");

};
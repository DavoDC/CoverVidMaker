#pragma once

// MediaFileList.h

// ### Headers
// Include common
#include "Common.h"
#include "MediaFile.h"

/**
 * @brief Represents a list of media files
*/
class MediaFileList {
public:
    // ### Constructors
	
	/**
	 * @brief Default constructor (required)
	*/
	MediaFileList();

	/**
	 * @param mediaFilePaths Media folder paths
	*/
	explicit MediaFileList(StringV mediaFolderPaths);


	// ### Public methods

	/**
	 * @return Number of media files
	*/
	int getFileNum() const;

	/**
	 * @return Audio file path at a given index
	*/
	const std::string getAudio(int index) const;

	/**
	 * @return Cover file path at a given index
	*/
	const std::string getCover(int index) const;

	/**
	 * @return Video file path at a given index
	*/
	const std::string getVideo(int index) const;

	/**
	 * @return Duration of audio file at a given index
	*/
	const std::string getDuration(int index) const;

	/**
	 * @return Total audio duration information
	*/
	const std::string getTotalDuration() const;

private:
   
	/**
	 * @brief Underlying data structure: vector of MediaFile objects
	*/
	std::vector<MediaFile> mediaFiles;

	/**
	 * @brief Number of media files
	*/
	int fileNum;

	/**
	 * @brief The total duration of the audio files.
	*/
	Seconds totalDuration;

};
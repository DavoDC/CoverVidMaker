#pragma once

// MediaFileList.h

// ### Headers
#include "Common.h"
#include "MediaFile.h"

/**
 * @brief Represents a list of media files.
*/
class MediaFileList {
public:
    // ### Constructors
	
	/**
	 * @brief Default constructor.
	*/
	MediaFileList();

	/**
	 * @param mediaFilePaths Media folder paths
	 * @param ffprobeFile ffprobe.exe file path
	*/
	explicit MediaFileList(StringV mediaFolderPaths, const std::string& ffprobeFile);


	// ### Public methods

	/**
	 * @return The number of media files found.
	*/
	int getFileNum() const;

	/**
	 * @return Audio file path at a given index.
	*/
	const std::string getAudio(int index) const;

	/**
	 * @return Cover file path at a given index.
	*/
	const std::string getCover(int index) const;

	/**
	 * @return Video file path at a given index.
	*/
	const std::string getVideo(int index) const;

	/**
	 * @return Duration of audio file at a given index.
	*/
	const std::string getDuration(int index) const;

	/**
	 * @return Total audio duration information.
	*/
	const std::string getTotalDuration() const;

private:
   
	/**
	 * @brief Underlying list of MediaFiles.
	*/
	std::vector<MediaFile> mediaFiles;

	/**
	 * @brief The number of media files found.
	*/
	int fileNum;

	/**
	 * @brief The total duration of the audio files.
	*/
	Seconds totalDuration;

};
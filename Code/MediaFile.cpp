// MediaFile.cpp

// Header
#include "MediaFile.h"

// Namespace mods
using namespace std;


// ### Constructor
MediaFile::MediaFile(const std::string& audioFilePath, StringV mediaFilePaths,
	Seconds duration) :
	audioFilePath(audioFilePath), duration(duration)
{
	// Extract media file/folder paths
	const string audioPath = mediaFilePaths[0];
	const string coverPath = mediaFilePaths[1];
	const string videoPath = mediaFilePaths[2];

	// Initialize cover and video file paths
	this->coverFilePath = getMediaFilePath(audioFilePath, audioPath, coverPath, ".png");
	this->videoFilePath = getMediaFilePath(audioFilePath, audioPath, videoPath, ".mp4");
}


// ### Public methods

const std::string MediaFile::getAudioFP() const {
	return quoteD(audioFilePath);
}

const std::string MediaFile::getCoverFP() const {
	return quoteD(coverFilePath);
}

const std::string MediaFile::getVideoFP() const {
	return quoteD(videoFilePath);
}

const std::string MediaFile::getDuration() const {
	return to_string(duration);
}


// ### Private methods

std::string MediaFile::getMediaFilePath(const std::string& filePath,
	const std::string& oldPath, const std::string& newPath,
	const std::string& newExtension, const std::string& oldExt) {
	std::string tempFilePath = filePath;
	replaceAll(tempFilePath, oldPath, newPath);
	replaceAll(tempFilePath, oldExt, newExtension);
	return tempFilePath;
}
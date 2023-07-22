// MediaFile.cpp

// Header
#include "MediaFile.h"

// Namespace mods
using namespace std;


// ### Constructor
MediaFile::MediaFile(const string& audioFilePath, StringV mediaFilePaths,
	Seconds duration) :
	audioFilePath(audioFilePath), duration(duration)
{
	// Extract media file/folder paths
	const string audioFolder = mediaFilePaths[0];
	const string coverFolder = mediaFilePaths[1];
	const string videoFolder = mediaFilePaths[2];

	// Initialize cover and video file paths
	this->coverFilePath = getMediaFilePath(audioFilePath, audioFolder, coverFolder, ".png");
	this->videoFilePath = getMediaFilePath(audioFilePath, audioFolder, videoFolder, ".mp4");
}


// ### Public methods

const string MediaFile::getAudioFP() const {
	return quoteD(audioFilePath);
}

const string MediaFile::getCoverFP() const {
	return quoteD(coverFilePath);
}

const string MediaFile::getVideoFP() const {
	return quoteD(videoFilePath);
}

const string MediaFile::getDuration() const {
	return to_string(duration);
}


// ### Private methods

string MediaFile::getMediaFilePath(const string& filePath,
	const string& oldPath, const string& newPath,
	const string& newExtension, const string& oldExt) {
	string tempFilePath = filePath;
	replaceAll(tempFilePath, oldPath, newPath);
	replaceAll(tempFilePath, oldExt, newExtension);
	return tempFilePath;
}
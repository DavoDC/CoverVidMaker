// MediaFileList.cpp

// Header
#include "MediaFileList.h"

// ### Libraries
#include <filesystem>

// Namespace mods
using namespace std;

// Macro for long iterator type
#define FSIterator filesystem::recursive_directory_iterator


// ### Constructors

MediaFileList::MediaFileList()
{
	this->fileNum = 0;
}

MediaFileList::MediaFileList(StringV mediaFolderPaths)
{
	// Extract audio path
	const string audioPath = mediaFolderPaths[0];

	// For every path in the Audio folder
	for (const auto& curPath : FSIterator(audioPath)) {

		// Convert current path to string
		string curPathS = curPath.path().generic_string();

		// If it is a MP3 file
		if (contains(curPathS, ".mp3")) {

			// Create MediaFile and add
			mediaFiles.push_back(MediaFile(curPathS, mediaFolderPaths));
		}
	}

	// If no MediaFiles added
	if (mediaFiles.empty())
	{
		// Notify and exit
		printErr("No MP3 files found in " + quoteS(audioPath), true);
	}

	// # Else if at least one file was added:
	// Save file count
	this->fileNum = int(mediaFiles.size());

	// Notify
	printSuccess(to_string(fileNum) + " MP3 Files Found");
}



// ### Public methods

const int MediaFileList::getFileNum() const
{
	return fileNum;
}


const std::string MediaFileList::getAudio(int index) const
{
	return mediaFiles[index].getAFP();
}

const std::string MediaFileList::getCover(int index) const
{
	return mediaFiles[index].getCFP();
}

const std::string MediaFileList::getVideo(int index) const
{
	return mediaFiles[index].getVFP();
}
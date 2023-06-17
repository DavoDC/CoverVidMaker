// MediaFileList.cpp

// Header
#include "MediaFileList.h"

// ### Libraries
#include <filesystem>

// Namespace mods
using namespace std;
using FSIterator = filesystem::recursive_directory_iterator;


// ### Constructors

MediaFileList::MediaFileList() : fileNum(0)
{
}

MediaFileList::MediaFileList(StringV mediaFolderPaths)
{
	// Extract audio path
	const string audioPath = mediaFolderPaths[0];

	// For every path in the Audio folder
	for (const auto& curPath : FSIterator(audioPath)) {

		// Convert current path to string
		const string curPathS = curPath.path().generic_string();

		// If it is a MP3 file
		if (curPath.path().extension() == ".mp3") {

			// Create MediaFile and add
			mediaFiles.emplace_back(curPathS, mediaFolderPaths);
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
	this->fileNum = static_cast<int>(mediaFiles.size());

	// Notify
	printSuccess(to_string(fileNum) + " MP3 Files Found");
}



// ### Public methods

int MediaFileList::getFileNum() const
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
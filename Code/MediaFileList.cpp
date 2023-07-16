// MediaFileList.cpp

// Header
#include "MediaFileList.h"
#include "Command.h"

// ### Libraries
#include <filesystem>

// Namespace mods
using namespace std;
using FSIterator = filesystem::recursive_directory_iterator;


// ### Constructors

MediaFileList::MediaFileList() 
	: fileNum(0), totalDuration(0)
{
}

MediaFileList::MediaFileList(StringV mediaFolderPaths, const string ffprobePath) 
	: MediaFileList()
{
	// Initialize duration command
	StringV durCommArgs = {
		"-v quiet -print_format",
		"compact=print_section=0:nokey=1:escape=csv -show_entries",
		"format=duration", Command::getMutArg(INPUT_AUDIO)
	};
	Command durComm = Command(ffprobePath, durCommArgs);

	// Extract audio path
	const string audioPath = mediaFolderPaths[0];

	// For every path in the Audio folder
	for (const auto& curPath : FSIterator(audioPath)) {

		// Convert current path to string
		const string curPathS = curPath.path().generic_string();

		// If it is a MP3 file
		if (curPath.path().extension() == ".mp3") {

			// Get duration
			durComm.updateArg(INPUT_AUDIO, quoteD(curPathS));
			durComm.run();
			double rawDur = stod(durComm.getOutput()) + 2;
			Seconds curDuration = static_cast<int>(round(rawDur));
			
			// Add to total duration
			totalDuration += curDuration;

			// Create MediaFile and add to list
			mediaFiles.emplace_back(curPathS, mediaFolderPaths, curDuration);
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

const string MediaFileList::getTotalDuration() const
{
	return format("{} minute(s)", to_string(totalDuration / 60));
}


const string MediaFileList::getAudio(int index) const
{
	return mediaFiles[index].getAFP();
}

const string MediaFileList::getCover(int index) const
{
	return mediaFiles[index].getCFP();
}

const string MediaFileList::getVideo(int index) const
{
	return mediaFiles[index].getVFP();
}


const string MediaFileList::getDuration(int index) const
{
	return mediaFiles[index].getDuration();
}
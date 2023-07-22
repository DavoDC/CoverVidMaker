// MediaFileList.cpp

// Header
#include "MediaFileList.h"
#include "Command.h"
#include "DurComm.h"

// Namespace mods
using namespace std;


// ### Constructors

MediaFileList::MediaFileList() : fileNum(0), totalDuration(0)
{
}

MediaFileList::MediaFileList(StringV mediaFolderPaths, const string& ffprobePath) : MediaFileList()
{
	// Initialize duration command
	DurComm durComm = DurComm(ffprobePath);

	// Iterate over audio files
	const string audioPath = mediaFolderPaths[0];
	FOR_EACH_AUDIO_FILE(audioPath) {

		// Get audio file path as a string
		const string curAudioFP = filePath.generic_string();

		// Get duration
		Seconds curDuration = durComm.getDuration(curAudioFP);
			
		// Add to total duration
		totalDuration += curDuration;

		// Create MediaFile and add to list
		mediaFiles.emplace_back(curAudioFP, mediaFolderPaths, curDuration);
	});

	// If no MediaFiles added, notify and exit
	if (mediaFiles.empty()) {
		printErr("No MP3 files found in " + quoteS(audioPath), true);
	}

	// # Else if at least one file was added:
	// Save file count
	this->fileNum = static_cast<int>(mediaFiles.size());

	// Notify
	printSuccess(to_string(fileNum) + " MP3 File(s) Found");
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
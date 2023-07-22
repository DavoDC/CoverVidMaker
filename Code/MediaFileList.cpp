// MediaFileList.cpp

// Header
#include "MediaFileList.h"
#include "Command.h"
#include "DurComm.h"
#include <regex>

// Namespace mods
using namespace std;

// File System Iterator Lambda Macro
namespace {
	auto iterateMP3Files = [](const fs::path& audioFolder,
		const function<void(const fs::path&)>& action) {
			for (const auto& entry : fs::recursive_directory_iterator(audioFolder)) {
				if (entry.path().extension() == L".mp3") {
					action(entry.path());
				}
			}
	};
}
#define FOR_EACH_AUDIO_FILE(PATH) iterateMP3Files(PATH, [&](const fs::path& filePath)


// ### Constructors

MediaFileList::MediaFileList() : fileNum(0), totalDuration(0)
{
}

MediaFileList::MediaFileList(StringV mediaFolderPaths, const string& ffprobePath) : MediaFileList()
{
	// Extract audio folder 
	const string audioFolder = mediaFolderPaths[0];

	// Iterate over raw audio files to sanitize them
	FOR_EACH_AUDIO_FILE(audioFolder) {

		// Get file name safely
		wstring curFilename = filePath.filename();
		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, curFilename.c_str(),
			-1, nullptr, 0, nullptr, nullptr);
		string sanitizedFilename(bufferSize, '\0');
		WideCharToMultiByte(CP_UTF8, 0, curFilename.c_str(), -1,
			&sanitizedFilename[0], bufferSize, nullptr, nullptr);

		// Replace " - " with " "
		replaceAll(sanitizedFilename, " - ", " ");

		// Remove any characters other than alphanumeric, space, and dot
		sanitizedFilename = regex_replace(sanitizedFilename, regex("[^a-zA-Z0-9 .]"), "");

		// Remove double spaces
		replaceAll(sanitizedFilename, "  ", " ");

		// Rename file to sanitized name
		int wideBufferSize = MultiByteToWideChar(CP_UTF8, 0,
			sanitizedFilename.c_str(), -1, nullptr, 0);
		wstring finalFilename(wideBufferSize, L'\0');
		MultiByteToWideChar(CP_UTF8, 0, sanitizedFilename.c_str(), -1,
			&finalFilename[0], wideBufferSize);
		fs::rename(filePath, filePath.parent_path() / finalFilename);
	});

	// Initialize duration command
	DurComm durComm = DurComm(ffprobePath);

	// Iterate over sanitized audio files
	FOR_EACH_AUDIO_FILE(audioFolder) {

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
		printErr("No MP3 files found in " + quoteS(audioFolder), true);
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
	return mediaFiles[index].getAudioFP();
}

const string MediaFileList::getCover(int index) const
{
	return mediaFiles[index].getCoverFP();
}

const string MediaFileList::getVideo(int index) const
{
	return mediaFiles[index].getVideoFP();
}


const string MediaFileList::getDuration(int index) const
{
	return mediaFiles[index].getDuration();
}
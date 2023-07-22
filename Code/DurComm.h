#pragma once

// DurComm.h

// ### Headers
#include "Common.h"
#include "MutComm.h"

/**
 * @brief Represents a terminal command that gets the duration of an audio file.
*/
class DurComm {
public:
	// ### Constructors

	/**
	 * @brief Construct a Duration Command.
	 * @param ffprobeFile The ffprobe.exe filepath.
	*/
	explicit DurComm(const std::string& ffprobeFile);


	// ### Public methods

	/**
	 * @return The duration of an audio file at a given filepath.
	*/
	Seconds getDuration(const std::string& audioFilePath);

private:

	// ### Private fields

	/**
	 * @brief Underlying Mutable Command
	*/
	MutComm command;
};
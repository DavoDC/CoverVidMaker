#pragma once

// DurComm.h

// ### Headers
#include "Common.h"
#include "Command.h"

/**
 * @brief Represents a terminal command that gets the duration of an audio file.
*/
class DurComm {
public:
	// ### Constructors

	/**
	 * @brief Constructor
	 * @param ffprobePath The ffprobe.exe filepath.
	*/
	explicit DurComm(const std::string& ffprobePath);


	// ### Public methods

	/**
	 * @return The duration of an audio file at a given filepath.
	*/
	Seconds getDuration(const std::string audioFilePath);

private:

	// ### Private fields

	/**
	 * @brief Underlying Command
	*/
	Command durationCommand;
};
#pragma once

// Command.h

// ### Headers
// Include common
#include "Common.h"

// Include needed headers
#include <windows.h>
#include <map>

// Map Type
using StringIntMap = std::map<std::string, int>;

// Mutable Argument String Constant
const std::string INPUT_AUDIO = "INPUT_AUDIO";


/**
 * @brief Represents a terminal command
*/
class Command {
public:
	// ### Constructors

	/**
	 * @brief Default constructor
	*/
	Command();

	/**
	 * @brief A command with no arguments.
	 * @param progName The program name.
	*/
	explicit Command(const std::string& progName);

	/**
	 * @brief A command with one argument.
	 * @param progName The program name.
	 * @param argument The argument.
	*/
	Command(const std::string& progName, const std::string& argument);

	/**
	 * @brief A command with multiple arguments.
	 * @param progName The program name.
	 * @param argList The argument list.
	*/
	Command(const std::string& progName, const StringV& argList);


	// ### Public methods

	/**
	 * @brief Run the command
	 * @param showOutput Toggles output (Default: false)
	*/
	void run(bool showOutput = false);

	/**
	 * @return String representation of command.
	*/
	std::string toString() const;

	/**
	 * @brief Print string representation of command.
	*/
	void printCommand() const;

	/**
	 * @return Console output of last run.
	*/
	std::string getOutput() const;

	/**
	 * @brief Print console output of last run.
	*/
	void printOutput() const;

	/**
	 * @return Time taken for the last run.
	*/
	double getTimeTaken() const;

	/**
	 * @return Format a given time taken value as a string
	*/
	static std::string formatTimeTaken(const double duration);

	/**
	 * @brief Print time taken for the last run.
	*/
	void printTimeTaken() const;

	/**
	 * @return The argument with the mutable arg delimiters added
	*/
	static std::string getMutArg(const std::string& rawArg);

	/**
	 * @brief Updates a given mutable arg to a given value.
	 * @param mutArgName The name of the mutable argument.
	 * @param newArgVal The new value for the argument.
	*/
	void updateArg(const std::string& mutArgName, const std::string& newArgVal);

private:

	// ### Constants

	/**
	 * @brief Mutable argument delimiter
	*/
	static const std::string maDelim;

	/**
	 * @brief Length of mutable argument delimiter
	*/
	static const size_t madLen;


	// ### Private fields

	/**
	 * @brief Program/command/executable name
	*/
	std::string progName;

	/**
	 * @brief Argument list
	*/
	StringV argList;

	/**
	 * @brief For looking up mutable argument positions
	*/
	StringIntMap mutableArgMap;

	/**
	 * @brief Console output of last run.
	*/
	std::string consoleOutput;

	/**
	 * @brief Time taken to run command during last run
	*/
	double duration;


	// ## Private methods

	/**
	 * @return A string representation of a given stream.
	*/
	std::string getStringFromStream(HANDLE streamHandle) const;
};
#pragma once

// Command.h

// ### Headers
// Include common
#include "Common.h"

// Include needed headers
#include <windows.h>

/**
 * @brief Represents a terminal command
*/
class Command {
public:
    // ### Constructors
    
    /**
     * @brief A command with no arguments.
     * @param progName The program name.
    */
    Command(const std::string& progName);

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
     * @return String representation of command.
    */
    std::string toString() const;

    /**
     * @brief Run command.
    */
    void run();
    
    /**
     * @brief Run command and print output.
    */
    void runWithOutput();

    /**
     * @brief Print output of last run.
    */
    void printOutput() const;

    /**
     * @return Output of last run.
    */
    std::string getOutput() const;

private:

    // ### Private fields
    
    /**
     * @brief Command line argument list
    */
    StringV cmdList;

    /**
     * @brief Console output of last run.
    */
    std::string output;


    // ## Private methods
    
    /**
     * @return A string representation of a given stream.
    */
    std::string getStringFromStream(HANDLE streamHandle);
};
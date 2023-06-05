#pragma once

// Command.h
// Represents a terminal command

// ### Headers
// Include common
#include "Common.h"

// Include needed headers
#include <windows.h>


class Command {
public:
    // Constructors
    Command(const std::string& progName);
    Command(const std::string& progName, const std::vector<std::string>& argList);

    // ### Public methods
    std::string toString() const;
    void run();
    void printOutput() const;
    void runWithOutput();
    std::string getOutput() const;

private:

    // ### Private fields
    // Command line argument list
    std::vector<std::string> cmdList;

    // Console output
    std::string output;

    // ## Private methods
    // Helper to convert output streams to strings
    std::string getStringFromStream(HANDLE streamHandle);
};
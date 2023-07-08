// Command.cpp

// Header
#include "Command.h"
#include <chrono>

// Namespace mods
using namespace std;

// Constants
// Mutable argument delimiter and length
const string Command::maDelim = "$$";
const size_t Command::madLen = maDelim.size();


// ### Constructors

Command::Command() :
    Command("ls")
{
    // Call constructor below with 'ls'
}

Command::Command(const string& progName) : 
    Command(progName, string()) 
{
    // Call constructor below with empty string.
}

Command::Command(const string& progName, const string& argument) : 
    Command(progName, StringV{argument})
{
    // Call constructor below with one argument
}

Command::Command(const string& progName, const StringV& argList) :
    progName(progName), argList(argList), duration(0)
{
    // Save arguments

    // ### Build mutable argument map

    // For each argument
    for (int i = 0; i < argList.size(); ++i) {

        // Extract argument
        const string& curArg = argList[i];

        // If argument is mutable (i.e has delimiters)
        if (curArg.size() > madLen * madLen &&
            curArg.substr(0, madLen) == maDelim &&
            curArg.substr(curArg.size() - madLen, madLen) == maDelim) {

            // Extract mutable argument name
            string mutArgName = curArg.substr(madLen, curArg.size() - madLen * madLen);

            // Save to map (key is name, position is value)
            mutableArgMap[mutArgName] = i;
        }
    }
}


// ### Public methods

void Command::run(bool showOutput) {

    // Get starting time
    auto startTime = chrono::high_resolution_clock::now();

    // Set security attributes
    SECURITY_ATTRIBUTES saAttr{};
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = nullptr;

    // Get output handle
    HANDLE stdOutRead, stdOutWrite;
    CreatePipe(&stdOutRead, &stdOutWrite, &saAttr, 0);
    SetHandleInformation(stdOutRead, HANDLE_FLAG_INHERIT, 0);

    // Set startup info
    STARTUPINFOA si{};
    si.cb = sizeof(STARTUPINFOA);
    si.hStdOutput = stdOutWrite;
    si.hStdError = stdOutWrite;
    si.dwFlags |= STARTF_USESTDHANDLES;

    // Process information reference
    PROCESS_INFORMATION pi{};

    // If process creation and execution successful
    if (CreateProcessA(
        nullptr, // nullptr to use the command string directly
        const_cast<char*>(toString().c_str()), // Command to be executed
        nullptr,  // Default process security attributes
        nullptr,  // Default process security attributes
        TRUE,     // Child process inherits handles
        0,        // Default creation flags
        nullptr,  // Use parent's environment block
        nullptr,  // Use parent's current directory
        &si,      // Startup information
        &pi       // Process information
    )) {
        CloseHandle(stdOutWrite); // Close the std output write handle
        consoleOutput = getStringFromStream(stdOutRead); // Extract std output
        CloseHandle(stdOutRead); // Close the std output read handle
        WaitForSingleObject(pi.hProcess, INFINITE); // Wait for the child process to exit
        CloseHandle(pi.hProcess); // Close the process handle
        CloseHandle(pi.hThread);  // Close the process's thread handle
    }
    else {
        // Else if execution fails, notify
        printErr("Command execution failed");
    }

    // Clean output
    replaceAll(consoleOutput, "\r", "");
    replaceAll(consoleOutput, "\n", "");

    // Print output if wanted
    if (showOutput) {
        printOutput();
    }

    // Get stop time
    auto stopTime = chrono::high_resolution_clock::now();

    // Calculate duration and save
    auto rawDur = duration_cast<chrono::milliseconds>(stopTime - startTime);
    duration = double(rawDur.count()) / 1000.0;
}

string Command::toString() const {
    
    // Initialize to program name
    string tempOutput = progName;

    // Append arguments
    for (const string& curArg : argList) {
        tempOutput.append(' ' + curArg);
    }

    // Return result
    return tempOutput;
}

void Command::printCommand() const {
    print(quoteS(" " + toString()));
}

string Command::getOutput() const {
    return consoleOutput;
}

void Command::printOutput() const {
    print("\n" + getOutput() + "\n");
}

double Command::getTimeTaken() const {
    return duration;
}

string Command::getTimeTaken(const double duration) {
    return format("Time taken: {} seconds", to_string(duration).erase(5));
}

void Command::printTimeTaken() const {
    print(getTimeTaken(duration));
}

string Command::getMutArg(const string& rawArg) {
    return maDelim + rawArg + maDelim;
}

void Command::updateArg(const string& mutArgName, const string& newArgVal) {

    // Look for mutable arg in map
    auto iter = mutableArgMap.find(mutArgName);

    // If found
    if (iter != mutableArgMap.end()) {

        // Retrieve the position of the argument in the argList
        int argPosition = iter->second;

        // Update the argument value at the specified position
        if (argPosition >= 0 && argPosition < argList.size()) {
            argList[argPosition] = newArgVal;
        }
    }
    else {
        // Else if not found, notify
        printErr("Mutable argument not found");
    }
}


// ## Private methods

string Command::getStringFromStream(HANDLE streamHandle) const {
    constexpr DWORD bufferSize = 4096;
    string tempOutput;
    DWORD bytesRead = 0;
    char buffer[bufferSize];
    while (ReadFile(streamHandle, buffer, bufferSize, &bytesRead, nullptr) && bytesRead > 0) {
        tempOutput.append(buffer, bytesRead);
    }
    return (tempOutput.length() < 3) ? "Empty!" : tempOutput;
}
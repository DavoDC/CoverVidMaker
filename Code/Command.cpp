// Command.cpp

// Header
#include "Command.h"

// Namespace mods
using namespace std;

// ### Constructors

Command::Command(const string& progName) : 
    Command(progName, string()) 
{
    // If only program name provided,
    // call constructor below with empty string.
}

Command::Command(const string& progName, const string& argument) : 
    Command(progName, StringV{argument})
{
    // Call constructor below with one argument
}

Command::Command(const string& progName, const StringV& argList) {

    // Concatenate into one string with spaces
    this->command = progName;
    for (const string& curArg : argList) {
        this->command += ' ' + curArg;
    }
}


// ### Public methods

string Command::toString() const {
    return this->command;
}

void Command::printCommand() const {
    print(quoteS(" " + this->command + " "));
}

void Command::run(bool showOutput) {

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
        const_cast<char*>(this->command.c_str()), // Command to be executed
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
        output = getStringFromStream(stdOutRead); // Extract std output
        CloseHandle(stdOutRead); // Close the std output read handle
        WaitForSingleObject(pi.hProcess, INFINITE); // Wait for the child process to exit
        CloseHandle(pi.hProcess); // Close the process handle
        CloseHandle(pi.hThread);  // Close the process's thread handle
    }
    else {
        // Else if execution fails, notify
        printErr("Command execution failed");
    }

    // Print output if wanted
    if (showOutput) {
        printOutput();
    }
}

string Command::getOutput() const {
    return output;
}

void Command::printOutput() const {
    print("\n" + getOutput() + "\n");
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

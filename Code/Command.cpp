// Command.cpp

// Header file
#include "Command.h"

// Namespace mods
using namespace std;

// Simple Command Constructor
// progName = Program/Executable name
Command::Command(const string& progName) : 
    Command(progName, string()) 
{
    // If only program name provided,
    // call constructor below with empty string.
}

// Simple Command Constructor
// progName = Program/Executable name
// argument = Single argument
Command::Command(const string& progName, const string& argument) : 
    Command(progName, StringV{argument})
{
    // Call constructor below with one argument
}

// Command Constructor
// progName = Program/Executable name
// argList = Argument list
Command::Command(const string& progName, const StringV& argList) {

    // Concatenate parameters
    string commS = progName + " ";
    for (const string& curArg : argList) {
        commS += curArg + " ";
    }

    // Add to list
    cmdList.push_back("cmd.exe");
    cmdList.push_back("/c");
    cmdList.push_back(commS);
}

// Get string representation of command
string Command::toString() const {
    return "\nCommand: \n" + cmdList[2];
}

// Run commmand
void Command::run() {

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

    // Convert command argument list to string
    string cmd = cmdList[0] + " " + cmdList[1] + " " + cmdList[2];

    // If process creation and execution successful
    if (CreateProcessA(
        nullptr, // nullptr to use the command string directly
        const_cast<char*>(cmd.c_str()), // Command to be executed
        nullptr,  // Default process security attributes
        nullptr,  // Default process security attributes
        TRUE,     // Child process inherits handles
        0,        // Ddefault creation flags
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
        print("Command execution failed");
    }
}

// Print output
void Command::printOutput() const {
    print("\n" + getOutput() + "\n");
}

// Run and print output
void Command::runWithOutput() {
    run();
    printOutput();
}

// Get output as a string
string Command::getOutput() const {
    return output;
}

// Helper to convert streams to strings
string Command::getStringFromStream(HANDLE streamHandle) {
    DWORD bytesRead;
    const int bufferSize = 4096;
    char buffer[bufferSize];
    string output = "";
    while (ReadFile(streamHandle, buffer, bufferSize, &bytesRead, nullptr) && bytesRead > 0) {
        output += string(buffer, bytesRead);
    }
    if (output.length() < 3) {
        output = "Empty!";
    }
    return output;
}

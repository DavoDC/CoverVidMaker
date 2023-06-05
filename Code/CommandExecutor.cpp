// CommandExecutor.cpp

// Header file
#include "CommandExecutor.h"

// ### Libraries
#include <iostream>
#include <windows.h>

// Namespace mods
using namespace std;


bool CommandExecutor::Execute(const wstring& command, const vector<wstring>& arguments) {

    // CreateProcess variables
    STARTUPINFOW startupInfo;
    PROCESS_INFORMATION processInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    ZeroMemory(&processInfo, sizeof(processInfo));

    // Create the command line string
    wstring commandLine = command;
    for (const wstring& argument : arguments) {
        commandLine += L" " + argument;
    }

    // Use try-catch block to handle any exceptions
    try {
        // CreateProcess parameters
        if (CreateProcessW(NULL, const_cast<LPWSTR>(commandLine.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
            // Wait for the process to complete
            WaitForSingleObject(processInfo.hProcess, INFINITE);

            // Get the exit code
            DWORD exitCode;
            GetExitCodeProcess(processInfo.hProcess, &exitCode);

            // Close process and thread handles
            CloseHandle(processInfo.hProcess);
            CloseHandle(processInfo.hThread);

            if (exitCode == 0) {
                wcout << L"Command executed successfully." << endl;
            }
            else {
                wcerr << L"Command failed with error code: " << exitCode << endl;
            }

            return true;
        }
        else {
            wcerr << L"Failed to create process." << endl;
            return false;
        }
    }
    catch (const exception& ex) {
        cerr << "An exception occurred: " << ex.what() << endl;
        return false;
    }
}

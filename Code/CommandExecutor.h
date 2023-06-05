#pragma once

// CommandExecutor.h
// Executes commands

// Libraries
#include <string>
#include <vector>

// Define class
class CommandExecutor {
public:
    bool Execute(const std::wstring& command, const std::vector<std::wstring>& arguments);
};
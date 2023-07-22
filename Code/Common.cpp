// Common.cpp

// Header file
#include "Common.h"

// ### Libraries
#include <iostream>
#include <iomanip>
#include <ranges>
#include <string_view>

// Namespace mods
using namespace std;


// ### Function Definitions

// # Printing Functions

void print(const string& s, bool useEndl)
{
    cout << "\n" << s;
    if (useEndl) {
        cout << endl;
    }
}

// Private helper
void printMessage(char startSymbol, const string& type, const string& msg)
{
    print(string(3, startSymbol) + " " + type + " " + quoteD(msg) + "!");
}

void printSuccess(const string& msg)
{
    printMessage('#', "SUCCESS", msg);
}

void printErr(const string& msg, bool exitAfter)
{
    printMessage('!', "ERROR", msg);

    if (exitAfter) {
        print("\n");
        exit(EXIT_FAILURE);
    }
}


// # String Functions

void replaceAll(string& source, const string& from, const string& to)
{
    string newString;
    newString.reserve(source.length()); // Avoids a few memory allocations
    string::size_type lastPos = 0;
    string::size_type findPos;
    while (string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }
    newString += source.substr(lastPos);
    source.swap(newString);
}

bool contains(const string& source, const string& query)
{
    return source.find(query) != string::npos;
}

string quoteS(const string& s)
{
    return "'" + s + "'";
}

string quoteD(const string& s)
{
    return "\"" + s + "\"";
}


// # Filesystem Functions

string getCleanPath(const string& path)
{
    // Remove surrounding quotes if they exist
    string cleanedPath = path;
    if (!cleanedPath.empty()
        && cleanedPath.front() == '"'
        && cleanedPath.back() == '"') {
        cleanedPath = cleanedPath.substr(1, cleanedPath.size() - 2);
    }
    return cleanedPath;
}

bool isPathValid(const string& path) {
    return fs::exists(fs::path(getCleanPath(path)));
}

bool isFileNonEmpty(const string& path) {

    // If file exists
    string cleanPath = getCleanPath(path);
    if (isPathValid(cleanPath)) {

        // Return true if non-empty,  false if empty
        return fs::file_size(cleanPath) != 0;
    } else {

        // Else if file doesn't exist, return false
        return false;
    }
}
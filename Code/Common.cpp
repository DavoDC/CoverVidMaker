// Common.cpp

// Header file
#include "Common.h"

// ### Libraries
#include <iostream>
#include <iomanip>
#include <ranges>
#include <string_view>
#include <filesystem>

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
    print("\n" + string(3, startSymbol) + " " + type + " " + quoteD(msg) + " !");
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

bool contains(const string& s1, const string& s2)
{
    return strstr(s1.c_str(), s2.c_str());
}

string quoteS(const string& s)
{
    return "'" + s + "'";
}

string quoteD(const string& s)
{
    return "\"" + s + "\"";
}


// # Other Functions

bool isPathValid(const string& path) {
    return filesystem::exists(path);
}
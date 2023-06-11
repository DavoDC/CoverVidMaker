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

void print(string s, bool useEndl)
{
	cout << "\n" << s;
	if (useEndl) {
		cout << endl;
	}
}

// Private helper
void printMessage(char startSymbol, string type, string msg)
{
	print("\n" + string(3, startSymbol) + " " + type + " " + quoteD(msg) + " !");
}

void printSuccess(string msg)
{
	printMessage('#', "SUCCESS", msg);
}

void printErr(string msg, bool exitAfter)
{
	printMessage('!', "ERROR", msg);

	if (exitAfter) {
		print("\n");
		exit(EXIT_FAILURE);
	}
}


// # String Functions

StringV split(string full, string sep)
{
	// Holder vector
	StringV parts;

	// For every part
	for (const auto curPart : ranges::views::split(full, sep)) {

		// Convert to string
		string curPartS = string(curPart.begin(), curPart.end());

		// Add to vector
		parts.push_back(curPartS);
	}

	// Return vector
	return parts;
}

StringV split(string fullS, string sep, int exp)
{
	// Holder vector
	StringV parts = split(fullS, sep);

	// Get parts length
	int pLen = int(parts.size());

	// If number of parts doesn't match expected
	if (pLen != exp)
	{
		// Notify
		print("WARNING: Split had unexpected results!");
		string pLenS = to_string(pLen);
		string expS = to_string(exp);
		print(format("Expected [{}] parts but got [{}]", expS, pLenS));
		print(format("Call: split({}, {}, {})", fullS, sep, exp), true);
	}

	// Return vector
	return parts;
}

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

bool contains(string s1, string s2)
{
	return strstr(s1.c_str(), s2.c_str());
}

string quoteS(string s)
{
	return "'" + s + "'";
}

string quoteD(string s)
{
	return "\"" + s + "\"";
}


// # Other Functions

bool isPathValid(const string path) {
	return filesystem::exists(path);
}
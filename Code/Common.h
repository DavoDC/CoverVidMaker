#pragma once

// Common.h
// Global essentials (e.g. helper functions)

// Global Libraries
#include <string>
#include <vector>
#include <format>

// String Vector Macro
#define StringV std::vector<std::string>


// ### Function Declarations


// # Printing Functions

/**
 * @brief Prints a given string.
 * @param s The string to print.
 * @param useEndl Toggle end line usage (Default: false).
*/
void print(std::string s, bool useEndl = false);

/**
 * @brief Prints a success message.
 * @param msg The message.
*/
void printSuccess(std::string msg);

/**
 * @brief Prints an error message.
 * @param msg The message.
 * @param exitAfter Toggle exiting after printing (Default: false)
*/
void printErr(std::string msg, bool exitAfter = false);



// # String Functions

/**
 * @brief Splits a string into parts using a given separator.
 * @param full The full string.
 * @param sep The separator string.
 * @return The parts as a vector of strings.
*/
StringV split(std::string full, std::string sep);

/**
 * @brief See split(). Also compares part count to expected count.
 * @param exp The expected number of parts.
*/
StringV split(std::string full, std::string sep, int exp);

/**
 * @brief Removes all substrings from a given string.
 * @param source The original string.
 * @param from The substring to replace.
 * @param to The string to be substituted in.
*/
void replaceAll(std::string& source, const std::string& from, const std::string& to);

/**
 * @param s1 The first string.
 * @param s2 The second string.
 * @return True if the first string contains the second.
*/
bool contains(std::string s1, std::string s2);

/**
 * @return The given string surrounded by a pair of single quotes.
*/
std::string quoteS(std::string s);

/**
 * @return The given string surrounded by a pair of double quotes.
*/
std::string quoteD(std::string s);
// MutComm.cpp

// Header
#include "MutComm.h"

// Namespace mod
using namespace std;

// Mutable argument delimiter and length
static const string delim = "$$";
static const size_t dLen = delim.size();

// ### Constructors

MutComm::MutComm(const std::string& progName, const StringV& argList)
{
    // ### Build mutable argument map

    // Flag for tracking if mutable argument found
    bool mutArgFound = false;

    // For each argument
    for (int i = 0; i < argList.size(); ++i) {

        // Extract argument
        const string& curArg = argList[i];

        // If argument is mutable
        if (isMutArg(curArg)) {

            // A mutable argument has been found
            mutArgFound = true;

            // Extract mutable argument name
            string mutArgName = curArg.substr(dLen, curArg.size() - dLen * dLen);

            // Save to map (key is name, position is value)
            mutableArgMap[mutArgName] = i;
        }
    }

    // If not mutable arguments found, notify and exit
    if (!mutArgFound) {
        printErr("No mutable arguments given to MutComm constructor", true);
    }
}

// ### Public Methods

string MutComm::getMutArg(const string& rawArg) {
    return delim + rawArg + delim;
}

void MutComm::updateMutArg(const string& mutArgName, const string& newArgVal) {

    // Look for mutable arg in map
    auto iter = mutableArgMap.find(mutArgName);

    // If mutable argument found
    if (iter != mutableArgMap.end()) {

        // Update the argument value at its position
        updateArg(iter->second, newArgVal);
    } else {

        // Else if not found, notify and exit
        printErr("Mutable Argument not found", true);
    }
}

// ### Private Methods

bool MutComm::isMutArg(const std::string& arg) {

    // If the argument size is less than twice the delimiter length
    if (arg.size() < dLen * 2) {

        // Return false as it cannot contain both delimiters
        return false;
    }

    // Return true if the argument starts and ends with the delimiters
    bool startsWithDelim = (arg.substr(0, dLen) == delim);
    bool endsWithDelim = (arg.substr(arg.size() - dLen, dLen) == delim);
    return startsWithDelim && endsWithDelim;
}
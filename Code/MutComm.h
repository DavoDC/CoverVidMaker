#pragma once

// MutComm.h

// ### Headers
#include "Common.h"
#include "Command.h"
#include <map>

// Map Type
using StringIntMap = std::map<std::string, int>;

// Mutable Argument Names
const std::string INPUT_AUDIO = "INPUT_AUDIO";
const std::string INPUT_COVER = "INPUT_COVER";
const std::string INPUT_DURATION = "INPUT_DURATION";
const std::string OUTPUT_VIDEO = "OUTPUT_VIDEO";
const std::string OUTPUT_COVER = "OUTPUT_COVER";

/**
 * @brief Represents a terminal command with mutable arguments.
 */
class MutComm : public Command {
public:
    // ### Constructors

    /**
     * @brief Construct a Mutable Command.
     * @param progName The program name.
     * @param argList The argument list.
    */
    MutComm(const std::string& progName, const StringV& argList);

    // ### Public Methods

    /**
     * @return The given argument with the mutable argument delimiters added.
    */
    static std::string getMutArg(const std::string& rawArg);

    /**
     * @brief Updates a given mutable argument to a given value.
     * @param mutArgName The raw name of the mutable argument (undelimited).
     * @param newArgVal The new value for the argument.
    */
    void updateMutArg(const std::string& mutArgName, const std::string& newArgVal);

private:
    // ### Private Fields

    /**
     * @brief Underlying map for looking up mutable argument positions.
    */
    StringIntMap mutableArgMap;

    // ### Private Methods

    /**
     * @return True if the given argument is a mutable argument (i.e. has delimiters).
    */
    bool isMutArg(const std::string& arg);

};

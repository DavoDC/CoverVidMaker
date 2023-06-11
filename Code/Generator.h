#pragma once

// Generator.h

// ### Headers
// Include common
#include "Common.h"

// Needed Headers
#include "Processor.h"

/**
 * @brief Generates media files
*/
class Generator {
public:
    // ### Constructor

    /**
     * @param proc File processor
    */
    Generator(Processor& proc);

private:
    // ### Private fields

    /**
     * @brief File processor reference
    */
    Processor& proc;


    // ### Private methods

    /**
     * @brief Extract album covers
    */
    void extractCovers();

};
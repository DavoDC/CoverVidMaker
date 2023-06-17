#pragma once

// Generator.h

// ### Headers
// Include common
#include "Common.h"

// Needed Headers
#include "Processor.h"
#include "Command.h"

/**
 * @brief Generates output files
*/
class Generator {
public:
    // ### Constructor

    /**
     * @param proc File processor
    */
    explicit Generator(Processor& proc);

private:
    // ### Private fields

    /**
     * @brief ffmpeg.exe file path
    */
    const std::string ffmpegPath;

    /**
     * @brief ffprobe.exe file path
    */
    const std::string ffprobePath;


    /**
     * @brief Media file list
    */
    MediaFileList mediaFiles;


    /**
     * @brief Number of media files
    */
    const int fileNum;


    /**
     * @brief Cover extraction command
    */
    Command coverComm;



    // ### Private methods

    /**
     * @brief Extract album covers
    */
    void extractCovers();

};
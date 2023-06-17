#pragma once

// Generator.h

// ### Headers
// Include common
#include "Common.h"

// Needed Headers
#include "Processor.h"
#include "Command.h"
#include <functional>

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

    /**
     * @brief Video maker command
    */
    Command vidComm;


    // ### Private methods

    /**
     * @brief Extract album covers from audio
    */
    void extractCovers();

    /**
     * @brief Make videos from audio and covers
    */
    void makeVideos();

    /**
     * @brief Generate media files
    */
    void generateMedia(const std::string& actionDesc, 
        std::function<std::string(int)> getMediaFilePath, 
        std::function<void(int)> generateCommand);

    /**
     * @brief Print an update based on files generated
    */
    void printUpdate(int filesGenerated);

};
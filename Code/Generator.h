#pragma once

// Generator.h

// ### Headers
// Include common
#include "Common.h"

// Needed Headers
#include "Processor.h"
#include "Command.h"
#include <functional>

// Function Types
using IntToStrFunc = std::function<std::string(int)>;
using IntFunc = std::function<void(int)>;


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
     * @brief Media file list.
    */
    MediaFileList mediaFiles;


    /**
     * @brief Number of media files.
    */
    const int fileNum;


    /**
     * @brief Cover extraction command.
    */
    Command coverComm;

    /**
     * @brief Video maker command.
    */
    Command vidComm;


    // ### Private methods

    /**
     * @brief Extract album covers from audio.
    */
    void extractCovers();

    /**
     * @brief Make videos from audio and covers.
    */
    void makeVideos();

    /**
     * @brief Generates media files.
     * @param actionDesc Describes the generation action.
     * @param getOutputPath Returns the path of the file to be generated.
     * @param runGenComm Updates the generation command and runs it.
    */
    void generateMedia(const std::string& actionDesc, 
        IntToStrFunc getOutputPath, IntFunc runGenComm);

    /**
     * @brief For printing periodic updates on generation progress.
    */
    void printUpdate(int filesGenerated);

};
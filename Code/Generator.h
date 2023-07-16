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
using PathGetter = std::function<std::string(int)>;
using GenComm = std::function<double(int)>;

// Mutable Argument String Constants
const std::string INPUT_COVER = "INPUT_COVER";
const std::string INPUT_DURATION = "INPUT_DURATION";
const std::string OUTPUT_VIDEO = "OUTPUT_VIDEO";
const std::string OUTPUT_COVER = "OUTPUT_COVER";


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
     * @brief Duration command.
    */
    Command durComm;

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
        PathGetter getOutputPath, GenComm runGenComm);

    /**
     * @brief For printing periodic updates on generation progress.
     * @param curFileNum The current number of files generated.
     * @param timeTaken The time taken for the last generation command.
    */
    void printUpdate(const int curFileNum, const double timeTaken);

};
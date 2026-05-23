#pragma once

// Generator.h

// ### Headers
#include "Common.h"
#include "Processor.h"
#include "MutComm.h"

// Function Types
using PathGetter = std::function<std::string(int)>;
using GenComm = std::function<double(int)>;

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
    const std::string ffmpegFile;


    /**
     * @brief Media file list.
    */
    MediaFileList mediaFiles;


    /**
     * @brief The number of media files.
    */
    const int fileNum;


    /**
     * @brief Cover extraction command.
    */
    MutComm coverComm;

    /**
     * @brief Video maker command.
    */
    MutComm vidComm;


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
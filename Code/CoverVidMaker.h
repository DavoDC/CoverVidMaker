#pragma once

// CoverVidMaker.h
// Converts MP3 audio files to MP4 videos using album covers

// ### Headers
// Include common
#include "Common.h"

// Include needed headers
//#include "MatchList.h"


// ### Libraries
// For set
//#include <set>


// ### Macros
// String set type
//#define StringSet std::set<std::string>



// Declare CoverVidMaker class
class CoverVidMaker {

public:

	// Constructor
	CoverVidMaker();

	// Analyse driver
	//void analyse();

	//// Settings
	//void toggleSampleData();
 //   void setCutoff(double);
	//void toggleColumnPrint();
	


private:
	// ### Private fields
	//// Use Sample Data
	//bool useSampleData;

	//// Percentage Cutoff Value
	//double cutoff;

	//// Column Printing
	//bool columnPrint;

	//// MatchList
	//MatchList ml;

	//// Number of matches
	//int matchNum;
	


	// ### Private methods
	// # Helpers
	//std::string getReplayPath();
	//void printColumns(std::string, std::string, std::string);
	//void printStatsLine(double, std::string, int);
	//void printSettingsUpdate(std::string);
	//void printStatsHeading(std::string);
	//void printDateStats();

	//// # Main Statistics Method
	//template <typename Property>
	//void printFreqStats(std::string, std::function<Property(Match)>);
};


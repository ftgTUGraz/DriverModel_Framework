#pragma once
#include "Parameters.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>


/**
* DataStorage class
*
* In the early stages of framework developement, it serves a purpose of storing the time stamps of 
* action trigger time. It is meant to be used in further developement for creating other necessary
* log files.
*
*/

class DataStorage
{
private:
    DataStorage();
	std::string file_name;
	std::ofstream out_file;

public:
	static DataStorage& instance()
	{
		static DataStorage instance;
		return instance;
	}

	/**
	* Write time stamp into log file when action is triggered.
	*
	* @param[time_stamp] time stamp to be written.
	*/

	void writeTimeStamp(double time_stamp);
};


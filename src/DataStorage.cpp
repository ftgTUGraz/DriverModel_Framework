#include "DataStorage.h"
#include <chrono>


DataStorage::DataStorage() 
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char buf[17] = { 0 };
	std::strftime(buf, sizeof(buf), "%Y-%m-%d-%H-%M", std::localtime(&now));
	

	this->file_name = "event_timestamps";
	this->file_name.append(buf);
	this->file_name.append(".txt");
	this->out_file.open(this->file_name);
}

void DataStorage::writeTimeStamp(double timeStamp)
{
	out_file << timeStamp << ", \n";
}


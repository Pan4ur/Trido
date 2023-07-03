#include "logger.h"

Logger::Logger()
{
	update_time();
	log_file.open(std::to_string(time->tm_year + 1900) + "-" + std::to_string(time->tm_mon + 1) + "-" + std::to_string(time->tm_mday) + ".log", std::ios::app);
}

void Logger::update_time()
{
	std::time_t t = std::time(nullptr);
	localtime_s(time, &t);
}

void Logger::print(int log_type, std::string text)
{
	update_time();
	log_file << "[" << (time->tm_hour < 10 ? "0" : "") << std::to_string(time->tm_hour) << ":" << (time->tm_min < 10 ? "0" : "") << 
		std::to_string(time->tm_min) << ":" << (time->tm_sec < 10 ? "0" : "") << std::to_string(time->tm_sec) << " ";
	if (log_type == INFO)
		log_file << "INFO";
	else if (log_type == WARNING)
		log_file << "WARNING";
	else if (log_type == ERROR)
		log_file << "ERROR";
	log_file << "] " << text << std::endl;
}
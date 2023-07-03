#pragma once
#include <fstream>
#include <ctime>
#include <string>

enum Log_type { INFO, WARNING, ERROR };
class Logger
{
public:
	Logger();
	void print(int log_type, std::string text);
private:
	void update_time();
	std::tm* time = new tm;
	std::ofstream log_file;
};
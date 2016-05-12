#pragma once

#include <string>
#include <fstream>
#include <mutex>

using namespace std;

class Logger
{
public:
	static Logger& Instance()
	{
		static Logger instance;
		return instance;
	}
	void Log(string);

private:
	Logger();
	void Config();

	mutex _m;
	string logfile;
};

#define LOG Logger::Instance().Log


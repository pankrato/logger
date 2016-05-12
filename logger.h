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
	void Log(string, ...);

private:
	Logger();
	~Logger();
	void Config();

	mutex _logguard;
	string _logfilename;
	ofstream _logfile;
};

#define LOG Logger::Instance().Log

enum {
	LOG_NONE	= 0x00,
	LOG_ERROR	= 0x10,
	LOG_WARNING	= 0x20,
	LOG_INFO	= 0x30,
	LOG_ALL		= 0xff
};


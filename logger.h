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

	static unsigned int _counter;
	mutex _logguard;
	string _logfilename;
	ofstream _logfile;
	bool _logtofile;
};

#define LOG Logger::Instance().Log


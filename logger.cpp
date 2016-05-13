
#include <iostream>
#include <sstream>
#include <ctime>
#include <thread>
#include "logger.h"

void Logger::log(const Level level, const string& str)
{
	// logs continuous numbering counter
	static unsigned int counter = 0;

	if (enabled && level >= loglevel) {
		lock_guard<mutex> lock(logguard); // RAII

		stringstream log;
		log	<< counter << " "
			<< clock() << " "
			<< level2string(level) << ": "
			<< str;

		cout << log.str() << endl;

		if (logtofile) {
			logfile << log.str() << endl;
		}

		counter++;
	}
}

Logger::Logger()
{
	logtofile = false;
	enabled = false;

	config();

	if (!logfilename.empty()) {
		logfile.open(logfilename);

		if (logfile) {
			logtofile = true;
			cout << "Logging to file " << logfilename << endl;
		}
	}
}

Logger::~Logger()
{
	logfile.close();
}

void Logger::enable(bool enable)
{
	enabled = enable;
}

void Logger::config(void)
{
	ifstream configfile ("config");

	if (configfile) {
		for (string line; getline(configfile, line); ) {

			auto pos = line.find("=");

			if (string::npos == pos) {	// no config option found
				continue;		// check the next line
			}
			// something found - store the findings
			auto key = line.substr(0, pos);
			auto value = line.substr(pos + 1);

			if ("enabled" == key) {
				if (("no" == value) || ("No" == value)) {
					enabled = false;
				} else {
					enabled = true;
				}
			}
			if ("filename" == key) {
				if ("default" == value) {
					time_t rawtime;
					struct tm * timeinfo;
					char buffer [80];

					time (&rawtime);
					timeinfo = localtime (&rawtime);

					strftime (buffer, 80, "%F-%X", timeinfo);
					logfilename = buffer;
					logfilename += ".log";
				} else if (!value.empty()) {
					logfilename = value;
				}
			}
			if ("level" == key) {
				if (("Default" == value) || ("default" == value)) {
					loglevel = Level::Default;
				} else if (("None" == value) || ("none" == value)) {
					loglevel = Level::None;
				} else if (("Error" == value) || ("error" == value)) {
					loglevel = Level::Error;
				} else if (("Warning" == value) || ("warning" == value)) {
					loglevel = Level::Warning;
				} else if (("Info" == value) || ("info" == value)) {
					loglevel = Level::Info;
				} else if (("All" == value) || ("all" == value)) {
					loglevel = Level::All;
				}
			}
		}
		configfile.close();
	}
}

void Logger::level(Level level)
{
	loglevel = level;
}

string Logger::level2string(Level level)
{
	string levstr = "";

	switch (level) {
		case Level::Error:
			levstr = "Error";
			break;
		case Level::Warning:
			levstr = "Warning";
			break;
		case Level::Info:
			levstr = "Info";
			break;
		default:
			levstr = "Bad";
	}
	return levstr;		
}


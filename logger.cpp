
#include <iostream>
#include <sstream>
#include <ctime>
#include "logger.h"

unsigned int Logger::_counter = 0;

void Logger::Log(string str, ...)
{
	lock_guard<mutex> lock(_logguard); // RAII

	stringstream log;
	log << _counter << " " << clock() << " " << str;

	cout << log.str() << endl;

	if (_logtofile) {
		_logfile << log.str() << endl;
	}

	_counter++;
}

Logger::Logger()
{
	_logtofile = false;
	_counter = 0;

	Config();

	if (!_logfilename.empty()) {
		_logfile.open(_logfilename);

		if (_logfile) {
			_logtofile = true;
			cout << "Logging to file " << _logfilename << endl;
		}
	}
}

Logger::~Logger()
{
	_logfile.close();
}

void Logger::Config(void)
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

			if ("filename" == key) {
				if ("default" == value) {
					time_t rawtime;
					struct tm * timeinfo;
					char buffer [80];

					time (&rawtime);
					timeinfo = localtime (&rawtime);

					strftime (buffer, 80, "%F-%X", timeinfo);
					_logfilename = buffer;
					_logfilename += ".log";
				} else {
					_logfilename = value;
				}
			}
		}
		configfile.close();
	}
}

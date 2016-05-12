
#include <iostream>
#include "logger.h"

void Logger::Log(string str, ...)
{
	lock_guard<mutex> lock(_logguard); // RAII
	cout << str << endl;
	_logfile << str << endl;
}

Logger::Logger()
{
	Config();

	if (!_logfilename.empty()) {
		_logfile.open(_logfilename);
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
				_logfilename = value;
				cout << "Logging to file " << value << endl;
			}
		}
	}
}

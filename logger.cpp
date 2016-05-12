
#include <iostream>
#include "logger.h"

void Logger::Log(string str)
{
	_m.lock();
	cout << str << endl;
	_m.unlock();
}

Logger::Logger()
{
	Config();
}

void Logger::Config(void)
{
	ifstream configfile ("config");

	if (configfile) {
		for (string line; getline(configfile, line); ) {
			cout << line << endl;
		}
	}
}

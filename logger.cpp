
#include <iostream>
#include "logger.h"

void Logger::Log(string str)
{
	_m.lock();
	cout << str << endl;
	_m.unlock();
}

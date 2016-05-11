#pragma once

#include <string>
#include <mutex>
#include "singleton.h"

using namespace std;

class Logger
{
private:
	mutex _m;
public:
	void Log(string);
	friend class Singleton<Logger>;
};

#define LOG Singleton<Logger>::Instance().Log


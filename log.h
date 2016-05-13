#pragma once

#include "logger.h"

class Log
{
public:
	static void i(const string& s)
	{
		instance().log(Level::Info, s);
	}
	static void w(const string& s)
	{
		instance().log(Level::Warning, s);
	}
	static void e(const string& s)
	{
		instance().log(Level::Error, s);
	}
	static void enable()
	{
		instance().enable(true);
	}
	static void disable()
	{
		instance().enable(false);
	}
	static void level(Level level)
	{
		instance().level(level);
	}


private:
	static Logger& instance()
	{
                static Logger logger;
                return logger;
        }

	// prohibited to be called from outside
	Log();
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;
};

class Loggable
{
protected:
	virtual string tostring() const = 0;

public:
	void log()
	{
		Log::i(tostring());
	}

};

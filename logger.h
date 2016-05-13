#pragma once

#include <string>
#include <fstream>
#include <mutex>

using namespace std;

enum class Level {
	All	= 0x00,
	Info	= 0x10,
	Warning	= 0x20,
	Error	= 0x30,
	None	= 0xff,
	Default	= All
};


class Logger
{
public:
	Logger();
	~Logger();

	// logging function
	void log(const Level, const string&);
	// enable/disable logging on the fly
	void enable(const bool);
	// set logging level on the fly
	void level(Level);

private:
	// logger configuration function
	void config();
	string level2string(Level);

	// mutex for critical section
	Level loglevel;
	// mutex for critical section
	mutex logguard;
	// name of the file to log to
	string logfilename;
	// output file stream for log messages
	ofstream logfile;
	// configuration flag to enable/disable logging as such
	bool enabled;
	// configuration flag enables logging to a file
	bool logtofile;
};


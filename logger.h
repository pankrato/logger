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
    void setLevel(Level);

private:
    // logger configuration function
    void config();
    string level2string(Level) const;

    // mutex for critical section
    Level mLogLevel;
    // mutex for critical section
    mutex mLogGuard;
    // name of the file to log to
    string mLogFileName;
    // output file stream for log messages
    ofstream mLogFile;
    // configuration flag to enable/disable logging as such
    bool mEnabled;
    // configuration flag enables logging to a file
    bool mLogToFile;
    // logs continuous numbering counter
    uint32_t mCounter;
};


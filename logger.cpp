#include <iostream>
#include <sstream>
#include <ctime>
#include <thread>
#include "logger.h"

using namespace std;

void Logger::log(const Level level, const string& str)
{
    if (mEnabled && level >= mLogLevel) {
        lock_guard<mutex> lock(mLogGuard); // RAII

        stringstream log;
        log	<< mCounter << " "
            << clock() << " "
            << level2string(level) << ": "
            << str;

        cout << log.str() << endl;

        if (mLogToFile) {
            mLogFile << log.str() << endl;
        }
        mCounter++;
    }
}

Logger::Logger()
{
    mLogToFile  = false;
    mEnabled    = false;
    mCounter    = 0;
    mLogLevel   = Level::Default;

	config();

    if (!mLogFileName.empty()) {
        mLogFile.open(mLogFileName);

        if (mLogFile) {
            mLogToFile = true;
            cout << "Logging to file " << mLogFileName << endl;
        }
    }
}

Logger::~Logger()
{
    mLogFile.close();
}

void Logger::enable(const bool enable)
{
    mEnabled = enable;
}

void Logger::config(void)
{
    ifstream configfile ("config");

    if (configfile) {
        for (string line; getline(configfile, line); ) {

            auto pos = line.find("=");

            if (string::npos == pos) {  // no config option found
                continue;               // check the next line
            }
            // something found - keep the findings
            auto key = line.substr(0, pos);
            auto value = line.substr(pos + 1);

            if ("enabled" == key) {
                if (("no" == value) || ("No" == value)) {
                    mEnabled = false;
                } else {
                    mEnabled = true;
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
                    mLogFileName = buffer;
                    mLogFileName += ".log";
                } else if (!value.empty()) {
                    mLogFileName = value;
                }
            }
            if ("level" == key) {
                if (("None" == value) || ("none" == value)) {
                    mLogLevel = Level::None;
                } else if (("Error" == value) || ("error" == value)) {
                    mLogLevel = Level::Error;
                } else if (("Warning" == value) || ("warning" == value)) {
                    mLogLevel = Level::Warning;
                } else if (("Info" == value) || ("info" == value)) {
                    mLogLevel = Level::Info;
                } else if (("All" == value) || ("all" == value)) {
                    mLogLevel = Level::All;
                } else {
                    mLogLevel = Level::Default;
                }
            }
        }
        configfile.close();
    }
}

void Logger::setLevel(Level level)
{
    mLogLevel = level;
}

string Logger::level2string(Level level) const
{
    switch (level) {
        case Level::Error:      return "Error";
        case Level::Warning:    return "Warning";
        case Level::Info:       return "Info";
        // fall through
        case Level::All:
        case Level::None:
        default:                break;
    }
    return "Wrong level!";
}


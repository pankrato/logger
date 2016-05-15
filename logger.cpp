#include <iostream>
#include <sstream>
#include <ctime>
#include <thread>
#include <algorithm>
#include "logger.h"

using namespace std;

void Logger::log(const Level level, const string& str)
{
    if (mEnabled && (level >= mLogLevel)) {
        lock_guard<mutex> lock(mLogGuard);

        stringstream log;
        log	<< mCounter << " "
            << clock() << " "
            << level2string(level) << ": "
            << str;

        cout << log.str() << endl;

        if (mLogFile.is_open()) {
            mLogFile << log.str() << endl;
        }
        mCounter++;
    }
}

Logger::Logger() :
    mEnabled(false),
    mCounter(1),
    mLogLevel(Level::Default)
{
	config();
}

Logger::~Logger()
{
    if (mLogFile.is_open()) {
        mLogFile.close();
    }
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

            transform(line.begin(), line.end(), line.begin(), ::tolower);
            auto pos = line.find("=");

            if (string::npos == pos) {  // no config option found
                continue;               // check the next line
            }
            // something found - keep the findings
            auto key = line.substr(0, pos);
            auto value = line.substr(pos + 1);

            if ("enabled" == key) {
                // value "no" (as well as "No", "NO", "nO")
                // will disable the logging
                if ("no" == value) {
                    mEnabled = false;
                // all other values will enable logging
                } else {
                    mEnabled = true;
                }
            }
            if ("filename" == key) {
                string filename = "";

                // by default the curent date and time
                // will be taken as a log file name
                if ("default" == value) {
                    time_t rawtime;
                    struct tm * timeinfo;
                    char buffer [80];

                    time (&rawtime);
                    timeinfo = localtime (&rawtime);

                    strftime (buffer, 80, "%F-%X", timeinfo);
                    filename = buffer;
                    filename += ".log";

                // any other non-empty string
                // will be taken as a log file name
                } else if (!value.empty()) {
                    filename = value;
                }

                if (!filename.empty()) {
                    mLogFile.open(filename);
                    if (mLogFile.is_open()) {
                        cout << "Will log to file " << filename << endl;
                    }
                }
            }
            if ("level" == key) {
                if ("none" == value) {
                    mLogLevel = Level::None;
                } else if ("error" == value) {
                    mLogLevel = Level::Error;
                } else if ("warning" == value) {
                    mLogLevel = Level::Warning;
                } else if ("info" == value) {
                    mLogLevel = Level::Info;
                } else if ("all" == value) {
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
        case Level::All:        // fall through
        case Level::None:       // fall through
        default:                return "Wrong level!";
    }
}


#include <fstream>
#include <mutex>
#include "log.h"

class Logger
{
public:
    Logger();
    ~Logger();

    // logging function
    void log(const Level, const std::string&);
    // enable/disable logging on the fly
    void enable(const bool);
    // set logging level on the fly
    void setLevel(Level);

private:
    // logger configuration function
    void config();
    static std::string level2string(Level);

    // configuration flag to enable/disable logging as such
    bool mEnabled;
    // logs continuous numbering counter
    uint32_t mCounter;
    // mutex for critical section
    Level mLogLevel;
    // mutex for critical section
    std::mutex mLogGuard;
    // output file stream for log messages
    std::ofstream mLogFile;
};


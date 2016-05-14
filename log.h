#pragma once

#include "logger.h"

class ILoggable
{
public:
    virtual std::string tostring() const = 0;
};

class Log
{
public:
    static void i(const std::string& s)
    {
        instance().log(Level::Info, s);
    }
    static void w(const std::string& s)
    {
        instance().log(Level::Warning, s);
    }
    static void e(const std::string& s)
    {
        instance().log(Level::Error, s);
    }
    static void l(const ILoggable& l)
    {
        instance().log(Level::Info, l.tostring());
    }
    static void enable()
    {
        instance().enable(true);
    }
    static void disable()
    {
        instance().enable(false);
    }
    static void setLevel(Level level)
    {
        instance().setLevel(level);
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


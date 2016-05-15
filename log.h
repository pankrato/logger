#pragma once

#include <string>

class Logger;

enum class Level {
    All     = 0x00,
    Info    = 0x10,
    Warning = 0x20,
    Error   = 0x30,
    None    = 0xff,
    Default = All
};

class ILoggable
{
public:
    virtual std::string tostring() const = 0;
};

class Log
{
public:
    static void i(const std::string&);
    static void w(const std::string&);
    static void e(const std::string&);
    static void l(const ILoggable&);
    static void enable();
    static void disable();
    static void setLevel(Level);

private:
    static Logger& instance();

    // prohibited to be called from outside
    Log();
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
};


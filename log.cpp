#include "logger.h"

Logger& Log::instance(void)
{
    static Logger logger;
    return logger;
}

void Log::i(const std::string& s)
{
    instance().log(Level::Info, s);
}

void Log::w(const std::string& s)
{
    instance().log(Level::Warning, s);
}

void Log::e(const std::string& s)
{
    instance().log(Level::Error, s);
}

void Log::l(const ILoggable& l)
{
    instance().log(Level::Info, l.tostring());
}

void Log::enable(void)
{
    instance().enable(true);
}

void Log::disable(void)
{
    instance().enable(false);
}

void Log::setLevel(Level level)
{
    instance().setLevel(level);
}


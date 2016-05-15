#include <thread>
#include <sstream>
#include <chrono>
#include "log.h"

using namespace std;

class MyType: public ILoggable
{
    uint32_t Re, Im;

public:
    MyType(): Re(0), Im(0) {}
    MyType(uint32_t re, uint32_t im): Re(re), Im(im) {}

    virtual string tostring() const
    {
        stringstream s;
        s << "MyType: Re: " << Re << ", Im: " << Im;
        return s.str();
    }
};

void thread_func(uint32_t threadno, uint32_t howmany)
{
    for (uint32_t i = 0; i < howmany; i++) {
        stringstream log;
        log << "Hello from thread " << threadno;
        Log::i(log.str());
    }
}

void Multithreading(uint32_t howmany = 10)
{
    uint32_t nthreads = thread::hardware_concurrency();
    thread thread_array[nthreads];

    for (uint32_t i = 0; i < nthreads; i++) {
        thread_array[i] = thread(thread_func, i, howmany);
    }
    for (uint32_t i = 0; i < nthreads; i++) {
        thread_array[i].join();
    }
}
// logging performance test
void TestPerformance(uint32_t howmany = 10)
{
    using namespace std::chrono;
    high_resolution_clock::time_point logstart, logend;
    duration<double> withlog, withoutlog;
    stringstream log;

    Log::enable();
    logstart = high_resolution_clock::now();
    Multithreading(howmany);
    logend = high_resolution_clock::now();
    withlog = duration_cast<duration<double>>(logend - logstart);
    log << "Test execution time with logging " << withlog.count() << " seconds.";
    Log::i(log.str());

    Log::disable();
    logstart = high_resolution_clock::now();
    Multithreading(howmany);
    logend = high_resolution_clock::now();
    withoutlog = duration_cast<duration<double>>(logend - logstart);
    Log::enable();
    log.str("");
    log << "Test execution time without logging " << withoutlog.count() << " seconds.";
    Log::i(log.str());
}
// set level test
void TestLevelSet(void)
{
    Log::setLevel(Level::Error);
    Log::e("Test error level");
    Log::w("Test warning level -- FAIL!"); // this log shall be omitted
    Log::setLevel(Level::Warning);
    Log::w("Test warning level -- pass"); // now shall be printed
    Log::setLevel(Level::Default);
}

// user type logging test
void TestUserTypeLog(void)
{
    MyType my(3, 5);
    Log::l(my); // will be logged with level "Info"
}

int main(void)
{
    uint32_t howmany = 10;

    Log::enable(); // just in case
    Log::setLevel(Level::Default);

    TestPerformance(howmany);
    TestLevelSet();
    TestUserTypeLog();

    return 0;
}


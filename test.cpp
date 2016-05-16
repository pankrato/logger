#include <thread>
#include <sstream>
#include <chrono>
#include <vector>
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
    vector<thread> threadv(nthreads);

    for (uint32_t i = 0; i < nthreads; i++) {
        threadv[i] = thread(thread_func, i, howmany);
    }
    for (uint32_t i = 0; i < nthreads; i++) {
        threadv[i].join();
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
// API test
void TestApi(void)
{
    Log::setLevel(Level::Info);
    Log::i("Test level info");
    Log::w("Test level warning");
    Log::e("Test level error");
    Log::setLevel(Level::Warning);
    Log::i("Test level info -- FAIL!");
    Log::w("Test level warning");
    Log::e("Test level error");
    Log::setLevel(Level::Error);
    Log::i("Test level info -- FAIL!");
    Log::w("Test level warning -- FAIL!");
    Log::e("Test level error");
    Log::disable();
    Log::i("Test level info -- FAIL!");
    Log::w("Test level warning -- FAIL!");
    Log::e("Test level error -- FAIL!");
    Log::enable();
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

    TestApi();
    TestPerformance(howmany);
    TestUserTypeLog();

    return 0;
}


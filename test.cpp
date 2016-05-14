
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

int main() {

	using namespace std::chrono;

	uint32_t howmany = 10;
	uint32_t nthreads = thread::hardware_concurrency();
	thread thread_array[nthreads];
	stringstream log;

	high_resolution_clock::time_point logstart, logend;
	duration<double> withlog, withoutlog;

	Log::enable();
	logstart = high_resolution_clock::now();

	for (uint32_t i = 0; i < nthreads; i++) {
		thread_array[i] = thread(thread_func, i, howmany);
	}

	for (uint32_t i = 0; i < nthreads; i++) {
		thread_array[i].join();
	}

	logend = high_resolution_clock::now();
	withlog = duration_cast<duration<double>>(logend - logstart);

	Log::disable();
	logstart = high_resolution_clock::now();

	for (uint32_t i = 0; i < nthreads; i++) {
		thread_array[i] = thread(thread_func, i, howmany);
	}

	for (uint32_t i = 0; i < nthreads; i++) {
		thread_array[i].join();
	}

	logend = high_resolution_clock::now();
	withoutlog = duration_cast<duration<double>>(logend - logstart);

	Log::enable();

	log << "Test execution time with logging " << withlog.count() << " seconds.";
	Log::i(log.str());
	log.str("");
	log << "Test execution time without logging " << withoutlog.count() << " seconds.";
	Log::i(log.str());

	// user type logging test
	MyType my_var(3, 5);
	my_var.log();

	// set level test
	Log::setLevel(Level::Error);
	Log::e("Test error level");
	Log::w("Test warning level"); // this log shall be omitted

	return 0;
}


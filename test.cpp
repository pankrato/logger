
#include <thread>
#include <sstream>
#include "logger.h"

using namespace std;

void thread_func(int threadno, int howmany)
{
	stringstream ss;
	ss << "Hello from tread " << threadno;

	for (int i = 0; i < howmany; i++) {
		LOG(ss.str());
	}
}

int main() {

	unsigned int howmany = 10;
	unsigned int nthreads = thread::hardware_concurrency();
	thread thread_array[nthreads];

	for (unsigned int i = 0; i < nthreads; i++) {
		thread_array[i] = thread(thread_func, i, howmany);
	}

	for (unsigned int i = 0; i < nthreads; i++) {
		if (thread_array[i].joinable()) {
			thread_array[i].join();
		}
	}

	return 0;
}


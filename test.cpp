
#include <thread>
#include <sstream>
#include "logger.h"

using namespace std;

void thread_func(int i)
{
	stringstream ss;
	ss << "Hello from tread " << i;
	LOG(ss.str());
	this_thread::sleep_for(chrono::seconds(1));
	LOG(ss.str());
}

int main() {

	const unsigned int nthreads = thread::hardware_concurrency();
	thread thread_array[nthreads];

	for (unsigned int i = 0; i < nthreads; i++) {
		thread_array[i] = thread(thread_func, i);
	}

	for (unsigned int i = 0; i < nthreads; i++) {
		if (thread_array[i].joinable()) {
			thread_array[i].join();
		}
	}

	return 0;
}


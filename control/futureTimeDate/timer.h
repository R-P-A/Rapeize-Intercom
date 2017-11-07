#ifndef TIMER
#define TIMER

#include <iostream>
#include <time.h>

using namespace std;

class Timer {
	private:
		time_t start, now;

	public:
		Timer();
		~Timer();

		unsigned long int getSecsSince1970();

		unsigned long int getSecsSinceLastCall();
};

#endif		// TIMER
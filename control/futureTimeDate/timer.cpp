#include <iostream>
#include <chrono>
#include "timer.h"

using namespace std;

Timer::Timer() {
	time(&start);
	time(&now);
}

Timer::~Timer() { }

unsigned long int Timer::getSecsSince1970() {
	return (unsigned long int) start;
}

unsigned long int Timer::getSecsSinceLastCall() {
	time_t previousNow = now;
	time(&now);
	return (unsigned long int) difftime(now, previousNow);
}
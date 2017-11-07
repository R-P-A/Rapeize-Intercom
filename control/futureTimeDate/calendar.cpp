#include "calendar.h"

#include <iostream>
using namespace std;

Calendar::Calendar (unsigned int year, unsigned int month, unsigned int day) {
	this->year = year;
	this->month = month;
	this->day = day;
}

Calendar::~Calendar() { }

void Calendar::setCalendar (unsigned int year, unsigned int month, unsigned int day) {
	this->year = year;
	this->month = month;
	this->day = day;
}

void Calendar::readCalendar (unsigned int& year, unsigned int& month, unsigned int& day){
	year = this->year;
	month = this->month;
	day = this->day;
}

void Calendar::advance () {
	day++;

	// Checks if isn't the most common option which is the other 28 days.
	if (day > 28) {
		if (month == 12 && day > 31) {			// December 31 days
			day = 1;
			month = 1;
			year++;
		} else if (month == 2 && day > 28) {	// February 28 days
			if (day > 29) {
				day = 1;
				month++;
			}
			if (!(((year % 400) == 0 ) || ((year % 4 == 0) && (year % 100 != 0)))) {	// Leap year February = 29 days
				day = 1;
				month++;
			}
		} else if (day > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10)) {
			day = 1;
			month++;
		} else if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
			day = 1;
			month++;
		}
	}
}
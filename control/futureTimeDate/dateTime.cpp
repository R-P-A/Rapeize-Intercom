#include "dateTime.h"

void DateTime::updateTimeDateInfo() {
	time_t secsSinceEpoch;
	time(&secsSinceEpoch);
	timeDateInfo = localtime(&secsSinceEpoch);
}

DateTime::DateTime() {
	updateTimeDateInfo();
}

DateTime::~DateTime() {
}

string DateTime::getCurrentDate() {
	updateTimeDateInfo();
	stringstream date;
	date << getYear() << "/" << getMonth() << "/" << getDay() << " " << getWeekDay();
	return date.str();
}

string DateTime::getCurrentTime() {
	updateTimeDateInfo();
	stringstream time;
	time.width(2);
	time.fill('0');
	time << getHour() << ":";
	time.width(2);
	time.fill('0');
	time << getMin() << ":";
	time.width(2);
	time.fill('0');
	time << getSec();
	return time.str();
}

string DateTime::getCurrentDateTime() {
	return getCurrentDate() + " " + getCurrentTime();
}

int DateTime::getYear() {
	return 1900 + timeDateInfo->tm_year;
}

int DateTime::getMonth() {
	return 1 + timeDateInfo->tm_mon;
}

int DateTime::getDay() {
	return timeDateInfo->tm_mday;
}

string DateTime::getWeekDay() {
	switch (timeDateInfo->tm_wday) {
		case 0:
			return "Sunday";
		case 1:
			return "Monday";
		case 2:
			return "Tuesday";
		case 3:
			return "Wednesday";
		case 4:
			return "Thursday";
		case 5:
			return "Friday";
		case 6:
			return "Saturday";
		default:
			return "error";
	}
}

int DateTime::getDaysYear() {
	return timeDateInfo->tm_yday;
}

int DateTime::getHour() {
	return timeDateInfo->tm_hour;
}

int DateTime::getMin() {
	return timeDateInfo->tm_min;
}

int DateTime::getSec() {
	return timeDateInfo->tm_sec;
}

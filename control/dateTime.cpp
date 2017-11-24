#include "dateTime.h"

DateTime::DateTime() {
	updateTimeDateInfo();
}

void DateTime::updateTimeDateInfo() {
	time_t secsSinceEpoch;
	time(&secsSinceEpoch);
	timeDateInfo = localtime(&secsSinceEpoch);
}

string DateTime::getCurrentDateTime() {
	updateTimeDateInfo();
	stringstream dateTime;
	dateTime << getYear() << "/" << getMonth() << "/" << getDay() << " " << getWeekDay() << " ";
	dateTime.width(2);
	dateTime.fill('0');
	dateTime << getHour() << ":";
	dateTime.width(2);
	dateTime.fill('0');
	dateTime << getMin() << ":";
	dateTime.width(2);
	dateTime.fill('0');
	dateTime << getSec();
	return dateTime.str();
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

int DateTime::getDaysYear() {
	return timeDateInfo->tm_yday;
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

int DateTime::getHour() {
	return timeDateInfo->tm_hour;
}

int DateTime::getMin() {
	return timeDateInfo->tm_min;
}

int DateTime::getSec() {
	return timeDateInfo->tm_sec;
}

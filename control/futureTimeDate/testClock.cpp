#include <iostream>
#include <chrono>

using namespace std;

#define secsYear 31536000
#define secs31days 2678400
#define secs30days 2592000
#define secs29days 2505600
#define secs28days 2419200
#define secsDay 86400
#define secsHour 3600
#define secsMin 60
#define brazilTime 3

unsigned long int getSecsSinceLastCall(time_t now) {
	time_t previousNow = now;
	time(&now);
	return (unsigned long int) difftime(now, previousNow);
}

int main() {
	time_t now;
	time(&now);
	unsigned int year, month, day, hour, min, sec, temp;
	unsigned long int months[12] = {secs31days, secs28days, secs31days, secs30days, secs31days, secs30days, secs31days, secs31days, secs30days, secs31days, secs30days, secs31days};
	hour = 0;
	min = 0;
	sec = 0;
	// Calculating the Year
	year = 1970;
	year += (now / secsYear);
	// Calculating the Month
	int i = 0;
	int leapYearDays = year/4 - year/100 + year/400 - (1970/4 - 1970/100 + 1970/400);
	now -= leapYearDays*secsDay;
	temp = now % secsYear;
	while (temp > months[i]) {
		i++;
		if (i == 1) {
			temp -= months[i];
		} else {
			temp -= months[i];
		}
	}
	month = ++i;
	// Calculating the Day
	day = (temp / secsDay) + 1;
	// Calculating the Hour
	temp %= secsDay;
	hour = (temp / secsHour) + 1 - brazilTime;
	// Calculating the Minute
	temp %= secsHour;
	min = (temp / secsMin) + 1;
	// Calculating the Seconds
	sec = temp % secsMin;
	cout << year << endl;
	cout << month << endl;
	cout << day << endl;
	cout << hour << endl;
	cout << min << endl;
	cout << sec << endl;
	return 0;
}
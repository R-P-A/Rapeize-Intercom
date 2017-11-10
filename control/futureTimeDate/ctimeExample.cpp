#include <iostream>
#include <ctime>

using namespace std;

int main() {
	time_t secsSinceEpoch;
	time(&secsSinceEpoch);

	cout << "Number of sec since January 1, 1970: " << secsSinceEpoch << endl;

	tm *timeInfo = localtime(&secsSinceEpoch);

	// print various components of tm structure.
	cout << "Year: " << 1900 + timeInfo->tm_year<<endl;
	cout << "Month: "<< 1 + timeInfo->tm_mon<< endl;
	cout << "Day: "<<  timeInfo->tm_mday << endl;
	cout << "Time: "<< timeInfo->tm_hour << ":";
	cout << timeInfo->tm_min << ":";
	cout << timeInfo->tm_sec << endl;
	cout << "Weekday: " << timeInfo->tm_wday << endl;
	cout << "Days since 01/01: " << timeInfo->tm_yday << endl;
	cout << "Daylight Saving Time: " << timeInfo->tm_isdst << endl << endl;

	timeInfo = gmtime(&secsSinceEpoch);

	// print various components of tm structure.
	cout << "Year: " << 1900 + timeInfo->tm_year<<endl;
	cout << "Month: "<< 1 + timeInfo->tm_mon<< endl;
	cout << "Day: "<<  timeInfo->tm_mday << endl;
	cout << "Time: "<< timeInfo->tm_hour << ":";
	cout << timeInfo->tm_min << ":";
	cout << timeInfo->tm_sec << endl;
	cout << "Weekday: " << timeInfo->tm_wday << endl;
	cout << "Days since 01/01: " << timeInfo->tm_yday << endl;
	cout << "Daylight Saving Time: " << timeInfo->tm_isdst << endl;

	return 0;
}
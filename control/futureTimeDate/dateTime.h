/** 
 *	@author  Rafael Pintar Alevato
 *	@date    07/11/2017
 *	@version 0.1 
 *	
 *	@brief Date and time tracking.
 *
 *	@section DESCRIPTION
 *	
 *	Creates a class that has a date (DD/MM/YYYY) and a time (HH:MM:SS)
 *	It can get current time and change its attributes. It does corrections for
 *	Brazil daylight saving time and leap years.
 */

#ifndef DATETIME
#define DATETIME

#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

class DateTime {
	private:
		tm* timeDateInfo;
		void updateTimeDateInfo();

	public:
		DateTime();
		~DateTime();
		string getCurrentDate();
		string getCurrentTime();
		string getCurrentDateTime();
		int getYear();
		int getMonth();
		int getDay();
		string getWeekDay();
		int getDaysYear();
		int getHour();
		int getMin();
		int getSec();
};


#endif	// DATETIME
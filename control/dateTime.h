/** 
 *	@author  Rafael Pintar Alevato
 *	@date    07/11/2017
 *	@version 1.0 
 *	
 *	@brief Date and time tracking.
 *
 *	@section DESCRIPTION
 *	
 *	Creates a class that has a date (DD/MM/YYYY) and a time (HH:MM:SS).
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
		/** Structure of ctime that stores date and time info based on seconds from Epoch. */
		tm* timeDateInfo;

	public:

		/**
		 *	Constructor that initializes the timeDateInfo.
		 */
		DateTime();

		/**
		 *	Function to update time and date of the structure timeDateInfo.
		 */
		void updateTimeDateInfo();
		
		/**
		 *	Get the currente date and time in the format "yyyy/mm/dd weekday hh:mm:ss".
		 *	@return	A string with the date and time.
		 */
		string getCurrentDateTime();
		
		/**
		 *	Get the current year updated according to last call of DateTime(), updateTimeDateInfo() or getCurrentDateTime().
		 *	@return	The year.
		 */
		int getYear();
		
		/**
		 *	Get the current month updated according to last call of DateTime(), updateTimeDateInfo() or getCurrentDateTime().
		 *	@return	The month.
		 */
		int getMonth();
		
		/**
		 *	Get the current day updated according to last call of DateTime(), updateTimeDateInfo() or getCurrentDateTime().
		 *	@return	The day.
		 */
		int getDay();
		
		/**
		 *	Get the current day since start of the year updated according to last call of DateTime(), updateTimeDateInfo() or getCurrentDateTime().
		 *	@return	The day since start of the year.
		 */
		int getDaysYear();
		
		/**
		 *	Get the current week day updated according to last call of DateTime(), updateTimeDateInfo() or getCurrentDateTime().
		 *	@return	The week day.
		 */
		string getWeekDay();
		
		/**
		 *	Get the current hour updated according to last call of DateTime(), updateTimeDateInfo() or getCurrentDateTime().
		 *	@return	The hour.
		 */
		int getHour();
		
		/**
		 *	Get the current minute updated according to last call of DateTime(), updateTimeDateInfo() or getCurrentDateTime().
		 *	@return	The minute.
		 */
		int getMin();
		
		/**
		 *	Get the current second updated according to last call of DateTime(), updateTimeDateInfo() or getCurrentDateTime().
		 *	@return	The second.
		 */
		int getSec();
};


#endif	// DATETIME
/** 
 *	@author  Rafael Pintar Alevato
 *	@date    17/09/2017
 *	@version 1.0 
 *	
 *	@brief Calendar and Clock that advances by one second.
 *
 *	@section DESCRIPTION
 *	
 *	Creates a simple clock and a calendar that calculates and advance its time
 *	in increments of one second.
 */

#ifndef CLOCKCALENDAR
#define CLOCKCALENDAR

#include <iostream>
#include "clock.h"
#include "calendar.h"
#include "myString.h"

using namespace std;

class ClockCalendar : public Clock, public Calendar {
	public:
		ClockCalendar (unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec, bool isPM);
		~ClockCalendar ();

		/** Advances the clock in one second and if needed (with isPM variable) advances the calendar in one day */
		void advance ();

		/** Print in a string the date and time */
		string toString();
};

#endif		// CLOCKCALENDAR
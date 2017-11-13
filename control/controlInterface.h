/** 
 *	@author  Rafael Pintar Alevato
 *	@date    13/11/2017
 *	@version 1.0 
 *	
 *	@brief Control Interface with pi and phone.
 *
 *	@section DESCRIPTION
 *	
 *	TODO.
 *
 */

#ifndef CONTROLINTERFACE
#define CONTROLINTERFACE

#include <iostream>
#include "user.h"
#include "sortedList.h"
#include "dateTime.h"

class ControlInterface {
	private:
		SortedList* activeUsers = new SortedList();
		
		TimeDate myTime;

	public:
		ControlInterface();

		~ControlInterface();

		void checkin(User currentUser);

		void checkout(User currentUser);

		SortedList getActiveUsers();

		void openDoor(User currentUser);

		void createUser(User inputUser);

		void removeUser(unsigned long int id);

		void editUser(User inputUser);

		User getUser(unsigned long int id);
	
};

#endif	// CONTROLINTERFACE
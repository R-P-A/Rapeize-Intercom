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
#include <fstream>
#include <string>
#include <iterator>
#include "myio.h"
#include "user.h"
#include "sortedList.h"
#include "dateTime.h"

using namespace std;

class ControlInterface {
	private:
		SortedList* activeUsers = new SortedList();
		
		DateTime myTime;

		string userDatabaseFileName;

		User* dbStringLineToUser(string& dbLine);

	public:
		ControlInterface();

		~ControlInterface();

		string getUserDatabaseName();

		void setUserDatabaseName(string name);

		void createUser(User* inputUser);

		void removeUser(unsigned long int id);

		void editUser(User* inputUser);

		User* getUser(unsigned long int id);

		User* getActiveUser(unsigned long int id);

		SortedList* getActiveUsers();

		void checkin(User* currentUser);

		void checkout(User* currentUser);

		void openDoor(User* currentUser);
	
};

#endif	// CONTROLINTERFACE
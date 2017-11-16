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

		User* databaseLineToUser(string& dbLine);

		void findUser(string& databaseString, size_t& initialPosition, size_t& finalPosition, unsigned long int id);

	public:
		ControlInterface();

		~ControlInterface();

		string getUserDatabaseName();

		void setUserDatabaseName(string name);

		void createUser(User* inputUser);

		User* readUser(unsigned long int id);

		void updateUser(User* inputUser);

		void deleteUser(unsigned long int id);

		void clearDatabase();

		User* getActiveUser(unsigned long int id);

		SortedList* getActiveUsers();

		void checkin(User* currentUser);

		void checkout(User* currentUser);

		void openDoor(User* currentUser);
	
};

#endif	// CONTROLINTERFACE
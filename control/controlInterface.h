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

		void getUserIdPass(string& inputUserIdPass, unsigned long int& inputUserId, string& inputUserPass);

		User* stringToUser(string& dbLine);

		void searchUserInDatabase(string& databaseString, size_t& initialPosition, size_t& finalPosition, unsigned long int id);

	public:
		ControlInterface();

		~ControlInterface();

		string getUserDatabaseName();

		void setUserDatabaseName(string name);

		void clearDatabase();

		void createUser(string inputUserString);

		string readUser(unsigned long int id);

		void updateUser(string inputUserString);

		void deleteUser(unsigned long int id);

		void checkin(string inputUserIdPass);

		void checkout(string inputUserIdPass);

		void openDoor(string inputUserIdPass);

		string getActiveUsers();
	
};

#endif	// CONTROLINTERFACE
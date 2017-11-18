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

#ifndef CENTRALCONTROL
#define CENTRALCONTROL

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include "myio.h"
#include "user.h"
#include "sortedList.h"
#include "dateTime.h"

using namespace std;

class CentralControl {
	private:
		SortedList* activeUsers = new SortedList();
		
		DateTime myTime;

		string userDatabaseFileName;

		void getUserIdPass(string& inputUserIdPass, unsigned long int& inputUserId, string& inputUserPass);

		User* stringToUser(string& dbLine);

		void searchUserInDatabase(string& databaseString, size_t& initialPosition, size_t& finalPosition, unsigned long int id);

	public:
		CentralControl();

		~CentralControl();

		bool isDatabaseClear();

		bool isUserCheckedin(unsigned long int id);

		bool canModifyDatabase(unsigned long int id);

		void createUser(string inputUserString, string currentUserIdPass);

		string readUser(unsigned long int id);

		void updateUser(string inputUserString, string currentUserIdPass);

		void deleteUser(unsigned long int id, string currentUserIdPass);

		void checkin(string currentUserIdPass);

		void checkout(string currentUserIdPass);

		unsigned long int openDoor(string currentUserIdPass);

		string getActiveUsers();
	
};

#endif	// CENTRALCONTROL
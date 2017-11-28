/** 
 *	@author  Rafael Pintar Alevato
 *	@date    13/11/2017
 *	@version 1.0 
 *	
 *	@brief Control that manages the database, checked-in users and the door opening.
 *
 *	@section DESCRIPTION
 *	
 *	The database is saved in a CSV format and the checked in users in a linked list.
 *
 */

#ifndef CENTRALCONTROL
#define CENTRALCONTROL

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <iterator>
#include <unistd.h>
#include "myio.h"
#include "user.h"
#include "sortedList.h"
#include "dateTime.h"

using namespace std;

class CentralControl {
	private:
		/**
		 *	Create a list to store all the checked-in users
		 */
		SortedList* activeUsers = new SortedList();
		
		/**
		 *	A time keeping variable to get current local time.
		 */
		DateTime myTime;

		/**
		 *	Name of the file used for the database.
		 */
		string userDatabaseFileName;

		/**
		 *	Transform a string with user data in csv format into a user.
		 *	@param dbLine User passed in the format "id,password,isAdmin,name,phone,email,beginWeekDay,endWeekDay,beginTime,endTime".
		 *	@return The pointer to the user created.
		 *	@throw const char* "Input line in the wrong format".
		 */
		User* stringToUser(string& dbLine);

		/**
		 *	Check if user exists in the database string and return its position if it does.
		 *	@param databaseString String with the database saved in a string.
		 *	@param initialPosition Initial position of the user in the string.
		 *	@param finalPosition Final position of the user in the string.
		 *	@param id The id of the user to search.
		 *	@throw const char* "Input line in the wrong format".
		 */
		void searchUserInDatabase(string& databaseString, size_t& initialPosition, size_t& finalPosition, unsigned long int id);

		/**
		 *	Convert week day in string format ("Monday") to a number from 0-6.
		 *	@param weekDay String with the week day in string format ("Monday").
		 *	@throw const char* "Wrong weekDay input".
		 */
		unsigned int weekDayToNumber(string weekDay);

		/**
		 *	Convert a time in string format ("hh:mm") to a number of seconds.
		 *	@param timeString String with the time in the following format ("hh:mm").
		 *	@throw const char* "Input line in the wrong format".
		 */
		unsigned long int timeStringToNumber(string timeString);

		/**
		 *	Update the web page with the current active users each time it changes the list.
		 *	@throw const char* "Input line in the wrong format".
		 */
		void updateHTML();

		/**
		 *	Open the door using the GPIO 4 of raspberry pi.
		 *	@throw const char* "Couldn't open the file".
		 *	@throw const char* "HTML Corrupted".
		 *	@throw const char* "Conversion from string to unsigned long int not valid".
		 *	@throw const char* "Active Users list corrupted".
		 */
		static void openDoorGPIO();

	public:
		/**
		 *	Constructor. Initialize the database.
		 *	@throw const char* "Couldn't open the file".
		 */
		CentralControl();

		/**
		 *	Destructor. Deletes the active users list.
		 */
		~CentralControl();

		/**
		 *	Check if the database is a clear.
		 *	@return Whether the database file clear ("").
		 *	@throw const char* "Couldn't open the file".
		 */
		bool isDatabaseClear();

		/**
		 *	Check if the user is checked-in.
		 *	@return Whether the user is checked-in.
		 */
		bool isUserCheckedin(unsigned long int id);

		/**
		 *	Check if the user is admin (can modify the database).
		 *	@return Whether the user is admin and if he is checked-in.
		 */
		bool canModifyDatabase(unsigned long int id);

		/**
		 *	Create a user in the database.
		 *	@param inputUserString The user data in the format "id,password,isAdmin,name,phone,email,beginWeekDay,endWeekDay,beginTime,endTime".
		 *	@param currentUserIdPass The id and pass of the user trying to modify the database. Format "id,password".
		 *	@throw const char* "Input line in the wrong format".
		 *	@throw const char* "Couldn't open the file".
		 *	@throw const char* "No permission to create user".
		 *	@throw const char* "First user isn't admin".
		 *	@throw const char* "User already exists".
		 */
		void createUser(unsigned long int currentUserId, string inputUserString);

		/**
		 *	Read a user in the database and return it.
		 *	@param id The id of the user to be read.
		 *	@param currentUserId The id of the user trying to read the database.
		 *	@return The user in the format "id,password,isAdmin,name,phone,email,beginWeekDay,endWeekDay,beginTime,endTime".
		 *	@throw const char* "Couldn't open the file".
		 *	@throw const char* "No permission to read user"
		 *	@throw const char* "User not found".
		 */
		string readUser(unsigned long int currentUserId, unsigned long int targetId);

		/**
		 *	Update a user that already exists in the database.
		 *	@param inputUserString The user updated data in the format "id,password,isAdmin,name,phone,email,beginWeekDay,endWeekDay,beginTime,endTime".
		 *	@param currentUserId The id of the user trying to modify the database.
		 *	@throw const char* "Input line in the wrong format".
		 *	@throw const char* "Couldn't open the file".
		 *	@throw const char* "No permission to update user".
		 *	@throw const char* "User not found".
		 */
		void updateUser(unsigned long int currentUserId, string inputUserString);

		/**
		 *	Delete a user that already exists in the database.
		 *	@param id The user id to be deleted.
		 *	@param currentUserId The id of the user trying to modify the database.
		 *	@param id The id of the user to be deleted.
		 *	@throw const char* "Couldn't open the file".
		 *	@throw const char* "No permission to delete user".
		 *	@throw const char* "User not found".
		 */
		void deleteUser(unsigned long int currentUserId, unsigned long int targetId);

		/**
		 *	Checkin with the current user accessing it.
		 *	@param currentUserId The id of the user trying to checkin.
		 *	@param currentUserPass The password of the user trying to checkin.
		 *	@throw const char* "Couldn't open the file".
		 *	@throw const char* "User not found".
		 *	@throw const char* "Input line in the wrong format".
		 *	@throw const char* "Password do not match".
		 *	@throw const char* "Wrong weekDay input".
		 *	@throw const char* "Current time before beginning time";
		 *	@throw const char* "Current time after ending time";
		 *	@throw const char* "Current day of the week before begin week day";
		 *	@throw const char* "Current day of the week after end week day";
		 *	@throw const char* "Inserted NULL Model".
		 *	@throw const char* "Id already exists".
		 */
		void checkin(unsigned long int currentUserId, string currentUserPass);

		/**
		 *	Checkin with the current user accessing it.
		 *	@param currentUserId The id of the user trying to checkout.
		 *	@throw const char* "Id not found".
		 */
		void checkout(unsigned long int currentUserId);

		/**
		 *	Checkin with the current user accessing it.
		 *	@param currentUserId The id of the user trying to open the door.
		 *	@throw const char* "User not checked-in".
		 */
		void openDoor(unsigned long int currentUserId);

		/**
		 *	Returns a list with all checked-in users in csv format (id,name,phone,email).
		 *	@throw const char* "Conversion from string to unsigned long int not valid".
		 *	@throw const char* "Active Users list corrupted".
		 */
		string getActiveUsers();
	
};

#endif	// CENTRALCONTROL
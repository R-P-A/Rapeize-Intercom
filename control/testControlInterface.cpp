#include <iostream>
#include "controlInterface.h"
#include "user.h"

using namespace std;

int main() {
	
	ControlInterface* tempCI = new ControlInterface();
	string tempString;

	tempCI->clearDatabase();

	cout << endl << "Try to instantiate one user with wrong inputs in beginWeekDay, endWeekDay, beginTime, endTime, one at a time." << endl;
	try {
		tempString = "14204800,pass,John,1010,john@doe.com,aonday,Friday,16:30,23:30\n";
		tempCI->createUser(tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		tempString = "14204800,pass,John,1010,john@doe.com,Tuesday,Frday,16:30,23:30\n";
		tempCI->createUser(tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		tempString = "14204800,pass,John,1010,john@doe.com,Tuesday,Friday,161:30,23:30\n";
		tempCI->createUser(tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		tempString = "14204800,pass,John,1010,john@doe.com,Tuesday,Friday,16:30,24:30\n";
		tempCI->createUser(tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to instantiate one user with missing inputs." << endl;
	try {
		tempString = "14204800,pass,John,1010\n";
		tempCI->createUser(tempString);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Create 4 users successfully." << endl;
	try {
		tempString = "14204800,pass,John,1010,john@doe.com,Tuesday,Friday,16:30,23:30\n";
		tempCI->createUser(tempString);
		tempString = "1380,pass,John,1010,john@doe.com,Tuesday,Friday,16:30,23:30\n";
		tempCI->createUser(tempString);
		tempString = "487,pass,John,1010,john@doe.com,Tuesday,Friday,16:30,23:30\n";
		tempCI->createUser(tempString);
		tempString = "856489,pass,John,1010,john@doe.com,Tuesday,Friday,16:30,23:30\n";
		tempCI->createUser(tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to create one user that already exists" << endl;
	try {
		tempCI->createUser(tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Read first, middle and last user successfully" << endl;
	try {
		cout << tempCI->readUser(14204800);
		cout << tempCI->readUser(1380);
		cout << tempCI->readUser(856489);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to read user that don't exist with an id that one existing user contains in his id" << endl;
	try {
		cout << tempCI->readUser(85648);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Update first, middle and last user successfully" << endl;
	try {
		tempString = "14204800,asf767h,Rafael,+5548981909090,rafael@rapeize.com,Monday,Friday,08:30,19:30\n";
		tempCI->updateUser(tempString);
		tempString = "1380,123,Kupas,454545,asf#se.com,Monday,Friday,08:30,19:30\n";
		tempCI->updateUser(tempString);
		tempString = "856489,123^sj,Ruan,gdfg333,asflkl)kduu,Monday,Friday,08:30,19:30\n";
		tempCI->updateUser(tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to update one user that don't exist with an id that one existing user contains in his id" << endl;
	try {
		tempString = "85648,123^sj,Ruan,gdfg333,asflkl,kduu,Monday,Friday,08:30,19:30\n";
		tempCI->updateUser(tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Checkin with first, middle and last user successfully." << endl;
	try {
		tempString = "14204800,asf767h";
		tempCI->checkin(tempString);
		tempString = "1380,123";
		tempCI->checkin(tempString);
		tempString = "856489,123^sj,";
		tempCI->checkin(tempString);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to checkin with one user that don't exist with an id that one existing user contains in his id." << endl;
	try {
		tempString = "1420480,asf767h";
		tempCI->checkin(tempString);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to checkin with one user that already is checked in." << endl;
	try {
		tempString = "14204800,asf767h";
		tempCI->checkin(tempString);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to checkin with one user with wrong pass." << endl;
	try {
		tempString = "487,pas";
		tempCI->checkin(tempString);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Delete first, middle and last user successfully" << endl;
	try {
		tempCI->deleteUser(14204800);
		tempCI->deleteUser(1380);
		tempCI->deleteUser(856489);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to delete one user that don't exist with an id that one existing user contains in his id" << endl;
	try {
		tempCI->deleteUser(48);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	delete tempCI;
	return 0;
}
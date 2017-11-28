#include <iostream>
#include <ctime>
#include "centralControl.h"
#include "user.h"

using namespace std;

int main() {
	system("rm userDatabase.csv");
	clock_t clocks = clock();

	CentralControl* tempCI;
	try {
		tempCI = new CentralControl();
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << "Is the database clear? " << tempCI->isDatabaseClear() << endl;
	
	string tempString, password;
	unsigned long int id;

	cout << endl << "Try to instantiate one user with wrong inputs in beginWeekDay, endWeekDay, beginTime, endTime, one at a time." << endl;
	try {
		tempString = "14204800,pass,1,John,1010,john@doe.com,aonday,Friday,08:30,23:30\n";
		id = 14204800;
		password = "pass";
		tempCI->createUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		tempString = "14204800,pass,1,John,1010,john@doe.com,Monday,Frday,08:30,23:30\n";
		tempCI->createUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		tempString = "14204800,pass,1,John,1010,john@doe.com,Monday,Friday,081:30,23:30\n";
		tempCI->createUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		tempString = "14204800,pass,1,John,1010,john@doe.com,Monday,Friday,08:30,24:30\n";
		tempCI->createUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to instantiate one user with missing inputs." << endl;
	try {
		tempString = "14204800,pass,1,John,1010\n";
		tempCI->createUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to create First user without admin permission. This user must be an admin and must be created for other changes in database." << endl;
	try {
		tempString = "14204800,pass,0,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
		tempCI->createUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Create First user successfully." << endl;
	try {
		tempString = "14204800,pass,1,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
		tempCI->createUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Get all active users. The result must be no user." << endl;
	try {
		cout << tempCI->getActiveUsers() << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Checkin with user 14204800. The user must be checked in to change the database." << endl;
	try {
		tempCI->checkin(id, password);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Create other 3 users successfully" << endl;
	try {
		tempString = "1380,pass,0,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
		tempCI->createUser(id, tempString);
		tempString = "487,pass,1,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
		tempCI->createUser(id, tempString);
		tempString = "856489,pass,0,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
		tempCI->createUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Get all active users. The result must be 14204800." << endl;
	try {
		cout << tempCI->getActiveUsers() << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Checkin with non admin user." << endl;
	try {
		id = 1380;
		password = "pass";
		tempString = "1380,pass,0,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
		tempCI->checkin(id, password);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to create one user without admin permission." << endl;
	try {
		tempString = "13800,pass,0,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
		tempCI->createUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to create one user that already exists" << endl;
	try {
		id = 14204800;
		password = "pass";
		tempString = "856489,pass,0,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
		tempCI->createUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Get all active users. The result must be 14204800 and 1380." << endl;
	try {
		cout << tempCI->getActiveUsers() << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Read first, middle and last user successfully" << endl;
	try {
		cout << tempCI->readUser(14204800, 14204800);
		cout << tempCI->readUser(14204800, 1380);
		cout << tempCI->readUser(14204800, 856489);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to read user that don't exist with an id that one existing user contains in his id" << endl;
	try {
		cout << tempCI->readUser(14204800, 85648);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Update first, middle and last user successfully" << endl;
	try {
		tempString = "14204800,asf767h,1,Rafael,+5548981909090,rafael@rapeize.com,Monday,Friday,08:30,19:30\n";
		tempCI->updateUser(id, tempString);
		tempString = "1380,123,0,Kupas,454545,asf#se.com,Monday,Friday,08:30,19:30\n";
		tempCI->updateUser(id, tempString);
		tempString = "856489,123^sj,0,Ruan,gdfg333,asflkl)kduu,Monday,Friday,08:30,19:30\n";
		tempCI->updateUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Read updated users" << endl;
	try {
		cout << tempCI->readUser(14204800, 14204800);
		cout << tempCI->readUser(14204800, 1380);
		cout << tempCI->readUser(14204800, 856489);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to update one user that don't exist with an id that one existing user contains in his id" << endl;
	try {
		tempString = "85648,123^sj,0,Ruan,gdfg333,asflkl)kduu,Monday,Friday,08:30,19:30\n";
		tempCI->updateUser(id, tempString);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Open door successfully with checked-in user" << endl;
	try {
		tempCI->openDoor(id);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to open door with non checked-in user" << endl;
	try {
		id = 856489;
		tempCI->openDoor(id);
		id = 14204800;
		password = "asf767h";
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Checkin with last user successfully." << endl;
	try {
		tempString = "123^sj";
		tempCI->checkin(856489, tempString);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to checkin with one user that don't exist with an id that one existing user contains in his id." << endl;
	try {
		tempString = "asf767h";
		tempCI->checkin(1420480, tempString);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to checkin with one user that already is checked in." << endl;
	try {
		tempString = "asf767h";
		tempCI->checkin(14204800, tempString);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to checkin with one user with wrong pass." << endl;
	try {
		tempString = "pas";
		tempCI->checkin(487, tempString);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Checkin with the same user with correct pass." << endl;
	try {
		tempString = "pass";
		tempCI->checkin(487, tempString);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Get all active users. The result must be all the users." << endl;
	try {
		cout << tempCI->getActiveUsers() << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Checkout with first, middle and last user successfully." << endl;
	try {
		tempString = "asf767h";
		tempCI->checkout(14204800);
		tempString = "123";
		tempCI->checkout(1380);
		tempString = "123^sj";
		tempCI->checkout(856489);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to checkout with already checked-out user." << endl;
	try {
		tempString = "asf767h";
		tempCI->checkout(14204800);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Get all active users. The result must be 487." << endl;
	try {
		cout << tempCI->getActiveUsers() << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Delete first, middle and last user successfully" << endl;
	try {
		id = 487;
		password = "pass";
		tempCI->deleteUser(id, 14204800);
		tempCI->deleteUser(id, 1380);
		tempCI->deleteUser(id, 856489);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to delete one user that don't exist with an id that one existing user contains in his id" << endl;
	try {
		tempCI->deleteUser(id, 48);
		cout << "Success!!!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	clocks = clock() - clocks;
	cout << "Total test runtime: " << (float) clocks / CLOCKS_PER_SEC << " s" << endl << endl;

	delete tempCI;
	return 0;
}
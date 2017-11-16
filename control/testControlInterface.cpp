#include <iostream>
#include "controlInterface.h"
#include "user.h"

using namespace std;

int main() {
	
	ControlInterface* tempCI = new ControlInterface();
	User* tempUser = new User();

	tempCI->clearDatabase();

	cout << endl << "Try to instantiate one user with wrong inputs in beginWeekDay, endWeekDay, beginTime, endTime, one at a time" << endl;
	try {
		tempUser->setId(14204800);
		tempUser->setName("John");
		tempUser->setPassword("pass");
		tempUser->setPhone("1010");
		tempUser->setEmail("john@doe.com");
		tempUser->setBeginWeekDay("aonday");
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		tempUser->setBeginWeekDay("Tuesday");
		tempUser->setEndWeekDay("Frday");
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		tempUser->setEndWeekDay("Friday");
		tempUser->setBeginTime("161:30");
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		tempUser->setBeginTime("16:30");
		tempUser->setEndTime("24:30");
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		tempUser->setEndTime("23:30");
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Create 4 users successfully" << endl;
	try {
		tempCI->createUser(tempUser);
		tempUser->setId(1380);
		tempCI->createUser(tempUser);
		tempUser->setId(487);
		tempCI->createUser(tempUser);
		tempUser->setId(856489);
		tempCI->createUser(tempUser);
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to create one user that already exists" << endl;
	try {
		tempCI->createUser(tempUser);
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Read first, middle and last user successfully" << endl;
	try {
		tempUser = tempCI->readUser(14204800);
		cout << tempUser->toString();
		tempUser = tempCI->readUser(1380);
		cout << tempUser->toString();
		tempUser = tempCI->readUser(856489);
		cout << tempUser->toString();
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to read user that don't exist with an id that one existing user contains in his id" << endl;
	try {
		tempUser = tempCI->readUser(85648);
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Update first, middle and last user successfully" << endl;
	try {
		tempUser->setId(14204800);
		tempUser->setName("Rafael");
		tempUser->setPassword("asf767h");
		tempUser->setPhone("+5548981909090");
		tempUser->setEmail("rafael@rapeize.com");
		tempUser->setBeginWeekDay("Monday");
		tempUser->setEndWeekDay("Friday");
		tempUser->setBeginTime("08:30");
		tempUser->setEndTime("19:30");
		tempCI->updateUser(tempUser);
		tempUser->setId(1380);
		tempUser->setName("Kupas");
		tempUser->setPassword("123");
		tempUser->setPhone("454545");
		tempUser->setEmail("asf#se.com");
		tempCI->updateUser(tempUser);
		tempUser->setId(856489);
		tempUser->setName("Ruan");
		tempUser->setPassword("123^sj");
		tempUser->setPhone("gdfg333");
		tempUser->setEmail("asflkl,kduu");
		tempCI->updateUser(tempUser);
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to update one user that don't exist with an id that one existing user contains in his id" << endl;
	try {
		tempUser->setId(85648);
		tempCI->updateUser(tempUser);
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Delete first, middle and last user successfully" << endl;
	try {
		tempCI->deleteUser(14204800);
		tempCI->deleteUser(1380);
		tempCI->deleteUser(856489);
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Try to delete one user that don't exist with an id that one existing user contains in his id" << endl;
	try {
		tempCI->deleteUser(48);
		cout << "Sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	delete tempUser;
	delete tempCI;
	return 0;
}
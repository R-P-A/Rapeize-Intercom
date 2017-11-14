#include <iostream>
#include "controlInterface.h"
#include "user.h"

using namespace std;

int main() {
	ControlInterface* temp = new ControlInterface();
	string fileName = "userDatabase.csv";
	string buffer = "";

	cout << endl << "Creating the file userDatabase.csv with nothing inside" << endl;
	try {
		writeFileClear(buffer, fileName);		
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Trying to find a user with no user inside" << endl;
	try {
		temp->getUser(1);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Creating a user in userDatabase.csv" << endl;
	User* tempUser = new User();
	try {
		tempUser->setId(14204800);
		tempUser->setName("Rafael");
		tempUser->setPassword("pass");
		tempUser->setPhone("1010");
		tempUser->setEmail("rafael@alevato.com");
		tempUser->setBeginWeekDay("Monday");
		tempUser->setEndWeekDay("Friday");
		tempUser->setBeginTime("16:30");
		tempUser->setEndTime("23:30");
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		temp->createUser(tempUser);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Creating another user in userDatabase.csv" << endl;
	try {
		tempUser->setId(8456);
		tempUser->setName("Ruan");
		tempUser->setPassword("1234");
		tempUser->setPhone("48999993333");
		tempUser->setEmail("ruan@molgero.com");
		tempUser->setBeginWeekDay("Monday");
		tempUser->setEndWeekDay("Friday");
		tempUser->setBeginTime("00:21");
		tempUser->setEndTime("23:59");
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		temp->createUser(tempUser);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Now creating another user with a wrong input format in userDatabase.csv" << endl;
	try {
		tempUser->setId(123562);
		tempUser->setName("Kupas");
		tempUser->setPassword("1234");
		tempUser->setPhone("48999993333");
		tempUser->setEmail("ygor@kupas.com");
		tempUser->setBeginWeekDay("onday");
		tempUser->setEndWeekDay("Friday");
		tempUser->setBeginTime("00:21");
		tempUser->setEndTime("23:59");
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		temp->createUser(tempUser);
	} catch (char const* e) {
		cout << e << endl;
	}

	User* tempUser2 = new User();
	cout << endl << "Trying to find 1420800 in userDatabase.csv" << endl;
	try {
		tempUser2 = temp->getUser(14204800);
		cout << tempUser2->getName() << endl;
		cout << "found!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Trying to find 8456 in userDatabase.csv" << endl;
	try {
		tempUser2 = temp->getUser(8456);
		cout << tempUser2->getName() << endl;
		cout << "found!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Trying to remove 8456 in userDatabase.csv" << endl;
	try {
		temp->removeUser(8456);
		cout << "Removed with sucess" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Trying to find 8456 again in userDatabase.csv" << endl;
	try {
		tempUser2 = temp->getUser(8456);
		cout << tempUser2->getName() << endl;
		cout << "found!" << endl;
	} catch (char const* e) {
		cout << e << endl;
	}

	delete tempUser;
	delete tempUser2;
	delete temp;
	return 0;
}
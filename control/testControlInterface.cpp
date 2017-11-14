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
		temp->findUser(1);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Creating a user in userDatabase.csv" << endl;
	User* tempUser;
	try {
		tempUser = new User(1, "Rafael", "1010", "john@doe.com", "0,5,08:00,18:00\n");
	} catch (char const* e) {
		cout << e << endl;
	}
	try {
		temp->createUser(tempUser);
	} catch (char const* e) {
		cout << e << endl;
	}

	cout << endl << "Trying to find the user in userDatabase.csv" << endl;
	User* tempUser2 = new User();
	try {
		tempUser2 = temp->findUser(1);
	} catch (char const* e) {
		cout << e << endl;
	}
	delete tempUser;
	delete tempUser2;
	delete temp;
	return 0;
}
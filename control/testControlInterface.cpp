#include <iostream>
#include "controlInterface.h"
#include "user.h"

using namespace std;

int main() {
	ControlInterface* temp = new ControlInterface();
	try {
		temp->findUser(1);
	} catch (char const* e) {
		cout << e << endl;
	}

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

	cout << "here\n";
	try {
		temp->findUser(1);
	} catch (char const* e) {
		cout << e << endl;
	}
	delete temp;
	return 0;
}
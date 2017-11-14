#include "controlInterface.h"

ControlInterface::ControlInterface() {
	// Turn on webserver
	userDatabaseName = "userDatabase.csv";
	string buffer = "";
	try {
		writeFileClear(buffer, userDatabaseName);		
	} catch (char const* e) {
		cout << e << endl;
	}
}

ControlInterface::~ControlInterface() {
	delete activeUsers;
}

string ControlInterface::getUserDatabaseName() {
	return userDatabaseName;
}

void ControlInterface::setUserDatabaseName(string name) {
	userDatabaseName = name;
}

void ControlInterface::createUser(User* inputUser) {
	try {
		findUser(inputUser->getId());
	} catch (char const* e) {
		if (e == "Couldn't open the file") {
			throw e;
		}
		string buffer = to_string(inputUser->getId()) + "," +
						inputUser->getName() + "," +
						inputUser->getPhone() + "," +
						inputUser->getEmail() + "," +
						inputUser->getAllowedPeriod();
		try {
			writeFileAppend(buffer, userDatabaseName);
		} catch (char const* e) {
			cout << e << endl;
		}
		return;
	}
	throw "Existing user";
}

void ControlInterface::removeUser(unsigned long int id) {
	
}

void ControlInterface::editUser(User* inputUser) {
	
}

User* ControlInterface::findUser(unsigned long int id) {
	string input;
	string buffer;
	ifstream inputFile(userDatabaseName.c_str());
	if (inputFile.is_open()) {
		int i = 0;
		while (getline(inputFile, input)){
			i = 0;
			int j = 0;
			for (j = 0, buffer = ""; input[i] != ','; i++, j++) {
				buffer[j] = input[i];
				cout << buffer[j];
			}
			cout << endl;
			if (id == stoi(buffer)) {
				User* output = new User();
				output->setName(buffer);
				for (j = 0, buffer = "", i++; input[i] != ','; i++, j++) {
					buffer[j] = input[i];
					cout << buffer[j];
				}
				cout << endl;
				output->setPhone(buffer);
				for (j = 0, buffer = "", i++; input[i] != ','; i++, j++) {
					buffer[j] = input[i];
					cout << buffer[j];
				}
				cout << endl;
				output->setEmail(buffer);
				for (j = 0, buffer = "", i++; input[i] != '\0'; i++, j++) {
					buffer[j] = input[i];
					cout << buffer[j];
				}
				cout << endl;
				buffer[j+1] = '\n';
				//cout << buffer << endl;
				output->setAllowedPeriod(buffer);
				return output;
			}
		}
		inputFile.close();
		throw "Couldn't find the user";
	} else {
		throw "Couldn't open the file";
	}
	return NULL;	// Sanity Check
}

User* ControlInterface::findActiveUser(unsigned long int id) {
	
}

SortedList* ControlInterface::getActiveUsers() {
	
}

void ControlInterface::checkin(User* currentUser) {
	
}

void ControlInterface::checkout(User* currentUser) {
	
}

void ControlInterface::openDoor(User* currentUser) {
	
}
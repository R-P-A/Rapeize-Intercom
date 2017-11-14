#include "controlInterface.h"

ControlInterface::ControlInterface() {
	// Turn on webserver
	userDatabaseName = "userDatabase.csv";
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
	User* bufferUser = new User();
	try {
		bufferUser = findUser(inputUser->getId());
	} catch (char const* e) {
		string str(e);
		if (str == "Couldn't open the file") {
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
	delete bufferUser;
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
		while (getline(inputFile, input)){
			int i = 0;
			for (buffer = ""; input[i] != ','; i++) {
				buffer += input[i];
			}
			if (id == stoul(buffer)) {
				User* output = new User();
				output->setId(stoul(buffer));

				for (buffer = "", i++; input[i] != ','; i++) {
					buffer += input[i];
				}
				output->setName(buffer);

				for (buffer = "", i++; input[i] != ','; i++) {
					buffer += input[i];
				}
				output->setPhone(buffer);

				for (buffer = "", i++; input[i] != ','; i++) {
					buffer += input[i];
				}
				output->setEmail(buffer);

				for (buffer = "", i++; input[i] != '\0'; i++) {
					buffer += input[i];
				}
				buffer += '\n';
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
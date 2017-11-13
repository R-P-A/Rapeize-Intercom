#include "controlInterface.h"

ControlInterface::ControlInterface() {
	// Turn on webserver
}

ControlInterface::~ControlInterface() {
	
}

void ControlInterface::createUser(User inputUser) {
	
}

void ControlInterface::removeUser(unsigned long int id) {
	
}

void ControlInterface::editUser(User inputUser) {
	
}

User* ControlInterface::findUser(unsigned long int id, string& fileName) {
	string input;
	string buffer;
	ifstream inputFile(fileName.c_str());
	if (inputFile.is_open()) {
		int i = 0;
		while (getline(inputFile, input)){
			i = 0;
			for (; input[i] != ','; i++) {
				buffer[i] = input[i];
			}
			if (id == stoi(buffer)) {
				User* output = new User();
				output->setName(buffer);
				for (; input[i] != ','; i++) {
					buffer[i] = input[i];
				}
				output->setPhone(buffer);
				for (; input[i] != ','; i++) {
					buffer[i] = input[i];
				}
				output->setEmail(buffer);
				for (; input[i] != '\n'; i++) {
					buffer[i] = input[i];
				}
				output->setAllowedPeriod(buffer);
				return output;
			}
		}
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

void ControlInterface::checkin(User currentUser) {
	
}

void ControlInterface::checkout(User currentUser) {
	
}

void ControlInterface::openDoor(User currentUser) {
	
}
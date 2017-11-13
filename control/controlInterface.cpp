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

User ControlInterface::getUser(unsigned long int id) {
	
}

SortedList ControlInterface::getActiveUsers() {
	
}

void ControlInterface::checkin(User currentUser) {
	
}

void ControlInterface::checkout(User currentUser) {
	
}

void ControlInterface::openDoor(User currentUser) {
	
}

// // For future use
// void readFileLine(string& output, string fileName) {
// 	string input;
// 	ifstream inputFile(fileName.c_str());
// 	if (inputFile.is_open()) {
// 		getStringLine(input, inputFile);
// 	} else {
// 		throw "Couldn't open the file";
// 	}
// 	output = input;
// 	return;
// }
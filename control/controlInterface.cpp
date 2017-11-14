#include "controlInterface.h"

ControlInterface::ControlInterface() {
	// Turn on webserver
	userDatabaseFileName = "userDatabase.csv";
}

ControlInterface::~ControlInterface() {
	delete activeUsers;
}

string ControlInterface::getUserDatabaseName() {
	return userDatabaseFileName;
}

void ControlInterface::setUserDatabaseName(string name) {
	userDatabaseFileName = name;
}

void ControlInterface::createUser(User* inputUser) {
	// Save the whole user database file in a string
	string buffer;
	try {
		readFile(buffer, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}
	// Try to find the inputUser id in the string
	size_t position = buffer.find(to_string(inputUser->getId()));
	// If it stopped before end of string
	if (position != string::npos) {
		throw "Existing user";
	}
	// Save in a string the new user with the correct format.
	buffer = to_string(inputUser->getId()) + "," +
			 inputUser->getName() + "," +
			 inputUser->getPassword() + "," +
			 inputUser->getPhone() + "," +
			 inputUser->getEmail() + "," +
			 inputUser->getBeginWeekDay() + "," +
			 inputUser->getEndWeekDay() + "," +
			 inputUser->getBeginTime() + "," +
			 inputUser->getEndTime() + "\n";
	// Write the new user the database appending to the end.
	try {
		writeFileAppend(buffer, userDatabaseFileName);
	} catch (char const* e) {
		cout << e << endl;
	}
}

void ControlInterface::removeUser(unsigned long int id) {
	try {
		User* bufferUser = new User();
		bufferUser = getUser(id);
		delete bufferUser;
	} catch (char const* e) {
		cout << e << endl;
	}

	string buffer;
	try {
		readFile(buffer, userDatabaseFileName);
	} catch (char const* e) {
		cout << e << endl;
	}

	size_t initialPosition = buffer.find(to_string(id));
	size_t finalPosition = buffer.find("\n", initialPosition);
	buffer.erase(initialPosition, (finalPosition - initialPosition + 1));

	try {
		writeFileClear(buffer, userDatabaseFileName);
	} catch (char const* e) {
		cout << e << endl;
	}
}

void ControlInterface::editUser(User* inputUser) {
	
}

User* ControlInterface::getUser(unsigned long int id) {
	string dbLine;
	string buffer;
	ifstream dbFile(userDatabaseFileName.c_str());
	if (dbFile.is_open()) {
		while (getline(dbFile, dbLine)){
			size_t position = dbLine.find(to_string(id));
			if (position != string::npos) {
				User* output = new User();
				output = dbStringLineToUser(dbLine);
				dbFile.close();
				return output;
			}
		}
		dbFile.close();
		throw "Couldn't find the user";
	} else {
		throw "Couldn't open the file";
	}
	return NULL;	// Sanity Check
}

User* ControlInterface::dbStringLineToUser(string& dbLine) {
	User* output = new User();
	string buffer;
	size_t prevPosition;
	size_t position;

	cout << dbLine << endl;

	position = dbLine.find(',');
	buffer = dbLine.substr(0, position);
	try {
		output->setId(stoul(buffer));	
	} catch (const unsigned char* e) {
		throw "Input database line corrupted";
	}
	

	prevPosition = position + 1;
	position = dbLine.find(',', prevPosition);
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setName(buffer);

	prevPosition = position + 1;
	position = dbLine.find(',', prevPosition);
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setPassword(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setPhone(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setEmail(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setBeginWeekDay(buffer);
	} catch (char const* e) {
		cout << e << endl;
	}

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setEndWeekDay(buffer);
	} catch (char const* e) {
		cout << e << endl;
	}

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setBeginTime(buffer);
	} catch (char const* e) {
		cout << e << endl;
	}

	prevPosition = position + 1;
	position = dbLine.find("\n", prevPosition);
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setEndTime(buffer);
	} catch (char const* e) {
		cout << e << endl;
	}

	return output;
}

User* ControlInterface::getActiveUser(unsigned long int id) {
	
}

SortedList* ControlInterface::getActiveUsers() {
	
}

void ControlInterface::checkin(User* currentUser) {
	
}

void ControlInterface::checkout(User* currentUser) {
	
}

void ControlInterface::openDoor(User* currentUser) {
	
}
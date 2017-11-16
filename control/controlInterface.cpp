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

User* ControlInterface::databaseLineToUser(string& dbLine) {
	User* output = new User();
	string buffer;
	size_t prevPosition;
	size_t position;

	position = dbLine.find(',');
	if (position == string::npos) {
		throw "Input database line in the wrong format";
	}
	buffer = dbLine.substr(0, position);
	try {
		output->setId(stoul(buffer));
	} catch (const unsigned char* e) {
		throw "Input database line in the wrong format";
	}

	prevPosition = position + 1;
	position = dbLine.find(',', prevPosition);
	if (position == string::npos) {
		throw "Input database line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setName(buffer);

	prevPosition = position + 1;
	position = dbLine.find(',', prevPosition);
	if (position == string::npos) {
		throw "Input database line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setPassword(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		throw "Input database line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setPhone(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		throw "Input database line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setEmail(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		throw "Input database line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setBeginWeekDay(buffer);
	} catch (char const* e) {
		throw e;
	}

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		throw "Input database line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setEndWeekDay(buffer);
	} catch (char const* e) {
		throw e;
	}

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		throw "Input database line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setBeginTime(buffer);
	} catch (char const* e) {
		throw e;
	}

	prevPosition = position + 1;
	position = dbLine.find("\n", prevPosition);
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setEndTime(buffer);
	} catch (char const* e) {
		throw e;
	}

	return output;
}

void ControlInterface::findUser(string& databaseString, size_t& initialPosition, size_t& finalPosition, unsigned long int id) {
	string idString = to_string(id);
	initialPosition = databaseString.find(idString);
	if (initialPosition == string::npos) {
		throw "User not found";
	}
	finalPosition = databaseString.find(",", initialPosition);
	if (idString == databaseString.substr(initialPosition, (finalPosition - initialPosition))) {
		finalPosition = databaseString.find("\n", initialPosition);
	} else {
		throw "User not found";
	}
}

void ControlInterface::createUser(User* inputUser) {
	string databaseString;
	string userString;
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}

	size_t initialPosition, finalPosition;
	try {
		findUser(databaseString, initialPosition, finalPosition, inputUser->getId());
	} catch (char const* e) {
		userString = inputUser->toString();

		try {
			writeFileAppend(userString, userDatabaseFileName);
		} catch (char const* e) {
			throw e;
		}
		return;
	}
	throw "User already exists";
}

User* ControlInterface::readUser(unsigned long int id) {
	string databaseString;
	string userString;
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}

	size_t initialPosition, finalPosition;
	try {
		findUser(databaseString, initialPosition, finalPosition, id);
	} catch (char const* e) {
		throw e;
	}

	User* output = new User();
	userString = databaseString.substr(initialPosition, (finalPosition - initialPosition + 1));
	output = databaseLineToUser(userString);
	return output;
}

void ControlInterface::updateUser(User* inputUser) {
	string databaseString;
	string userString;
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}

	size_t initialPosition, finalPosition;
	try {
		findUser(databaseString, initialPosition, finalPosition, inputUser->getId());
	} catch (char const* e) {
		throw e;
	}

	userString = inputUser->toString();

	databaseString.replace(initialPosition, (finalPosition - initialPosition + 1), userString);

	try {
		writeFileClear(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}
}

void ControlInterface::deleteUser(unsigned long int id) {
	string databaseString;
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}

	size_t initialPosition, finalPosition;
	try {
		findUser(databaseString, initialPosition, finalPosition, id);
	} catch (char const* e) {
		throw e;
	}
	
	databaseString.erase(initialPosition, (finalPosition - initialPosition + 1));

	try {
		writeFileClear(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}
}

void ControlInterface::clearDatabase() {
	string databaseString = "";
	try {
		writeFileClear(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}
}

User* ControlInterface::getActiveUser(unsigned long int id) {
	
}

SortedList* ControlInterface::getActiveUsers() {
	
}

void ControlInterface::checkin(User* currentUser) {
	// User* tempUser = new User();
	// tempUser = activeUsers->find(currentUser->getId());
}

void ControlInterface::checkout(User* currentUser) {
	
}

void ControlInterface::openDoor(User* currentUser) {
	
}
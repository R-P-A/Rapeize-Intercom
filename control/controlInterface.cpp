#include "controlInterface.h"

ControlInterface::ControlInterface() {
	userDatabaseFileName = "userDatabase.csv";
	string databaseString, buffer;
	size_t position, prevPosition;
	bool notDone = true;
	hasAdmin = false;

	// Turn on webserver
	// ...

	// Initialize database
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}
	try {
		if (databaseString == "" || databaseString == "\n") {
			return;
		}
		while (notDone) {
			position = databaseString.find(',');
			if (position == string::npos) {
				clearDatabase();
				throw "Database corrupted! All data is lost!";
			}
			prevPosition = position + 1;
			position = databaseString.find(',', prevPosition);
			prevPosition = position + 1;
			position = databaseString.find(',', prevPosition);
			buffer = databaseString.substr(prevPosition, position - prevPosition);
			if (to_bool(buffer)) {
				hasAdmin = true;
				notDone = false;
			}
			position = databaseString.find('\n');
		}
	} catch (char const* e) {
		throw e;
	}
}

ControlInterface::~ControlInterface() {
	delete activeUsers;
}

void ControlInterface::getUserIdPass(string& inputUserIdPass, unsigned long int& inputUserId, string& inputUserPass) {
	size_t position;
	size_t prevPosition;
	string tempId;

	position = inputUserIdPass.find(',');
	if (position == string::npos) {
		throw "Input line in the wrong format";
	}
	tempId = inputUserIdPass.substr(0, position);
	try {
		inputUserId = stoul(tempId);
	} catch (const char* e) {
		throw "Input line in the wrong format";
	}

	prevPosition = position + 1;
	position = inputUserIdPass.find(',', prevPosition);
	inputUserPass = inputUserIdPass.substr(prevPosition, position - prevPosition);
}

User* ControlInterface::stringToUser(string& dbLine) {
	User* output = new User();
	string buffer;
	size_t prevPosition;
	size_t position;

	position = dbLine.find(',');
	if (position == string::npos) {
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(0, position);
	try {
		output->setId(stoul(buffer));
	} catch (const char* e) {
		throw "Input line in the wrong format";
	}

	prevPosition = position + 1;
	position = dbLine.find(',', prevPosition);
	if (position == string::npos) {
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setPassword(buffer);

	prevPosition = position + 1;
	position = dbLine.find(',', prevPosition);
	if (position == string::npos) {
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setIsAdmin(to_bool(buffer));
	} catch (const char* e) {
		throw "Input line in the wrong format";
	}

	prevPosition = position + 1;
	position = dbLine.find(',', prevPosition);
	if (position == string::npos) {
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setName(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setPhone(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setEmail(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		throw "Input line in the wrong format";
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
		throw "Input line in the wrong format";
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
		throw "Input line in the wrong format";
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

void ControlInterface::searchUserInDatabase(string& databaseString, size_t& initialPosition, size_t& finalPosition, unsigned long int id) {
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

void ControlInterface::clearDatabase() {
	string databaseString = "";
	try {
		writeFileClear(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}
}

void ControlInterface::createUser(string inputUserString) {
	string databaseString;
	User* inputUser = new User();

	try {
		inputUser = stringToUser(inputUserString);
	} catch (char const* e) {
		delete inputUser;
		throw e;
	}

	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		delete inputUser;
		throw e;
	}

	size_t initialPosition, finalPosition;
	try {
		searchUserInDatabase(databaseString, initialPosition, finalPosition, inputUser->getId());
	} catch (char const* e) {
		try {
			writeFileAppend(inputUserString, userDatabaseFileName);
		} catch (char const* e) {
			delete inputUser;
			throw e;
		}
		delete inputUser;
		return;
	}
	delete inputUser;
	throw "User already exists";
}

string ControlInterface::readUser(unsigned long int id) {
	string databaseString;
	string userString;
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}

	size_t initialPosition, finalPosition;
	try {
		searchUserInDatabase(databaseString, initialPosition, finalPosition, id);
	} catch (char const* e) {
		throw e;
	}

	userString = databaseString.substr(initialPosition, (finalPosition - initialPosition + 1));
	return userString;
}

void ControlInterface::updateUser(string inputUserString) {
	string databaseString;
	User* inputUser = new User();

	try {
		inputUser = stringToUser(inputUserString);
	} catch (char const* e) {
		delete inputUser;
		throw e;
	}
	
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		delete inputUser;
		throw e;
	}

	size_t initialPosition, finalPosition;
	try {
		searchUserInDatabase(databaseString, initialPosition, finalPosition, inputUser->getId());
	} catch (char const* e) {
		delete inputUser;
		throw e;
	}

	databaseString.replace(initialPosition, (finalPosition - initialPosition + 1), inputUserString);

	try {
		writeFileClear(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		delete inputUser;
		throw e;
	}
	delete inputUser;
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
		searchUserInDatabase(databaseString, initialPosition, finalPosition, id);
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

void ControlInterface::checkin(string inputUserIdPass) {
	string databaseUser;
	unsigned long int inputUserId, dbUserId;
	string inputUserPass, dbUserPass;

	try {
		getUserIdPass(inputUserIdPass, inputUserId, inputUserPass);
	} catch (const char* e) {
		throw e;
	}

	try {
		databaseUser = readUser(inputUserId);
	} catch (const char* e) {
		throw e;
	}

	try {
		getUserIdPass(databaseUser, dbUserId, dbUserPass);
	} catch (const char* e) {
		throw e;
	}

	if (dbUserPass == inputUserPass) {
		User* checkinUser = new User();
		try {
			checkinUser = stringToUser(databaseUser);
		} catch (const char* e) {
			delete checkinUser;
			throw e;
		}
		try {
			activeUsers->insert(checkinUser);
		} catch (const char* e) {
			delete checkinUser;
			throw e;
		}
		system("echo Door opened!\n");
	} else {
		throw "Password do not match";
	}	
}

void ControlInterface::checkout(string inputUserIdPass) {
	
}

void ControlInterface::openDoor(string inputUserIdPass) {
	
}

string ControlInterface::getActiveUsers() {
	
}
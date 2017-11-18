#include "centralControl.h"

CentralControl::CentralControl() {
	userDatabaseFileName = "userDatabase.csv";
	string databaseString;

	// Turn on webserver
	// ...

	// Initialize database
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}
}

CentralControl::~CentralControl() {
	delete activeUsers;
}

void CentralControl::getUserIdPass(string& inputUserIdPass, unsigned long int& inputUserId, string& inputUserPass) {
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

User* CentralControl::stringToUser(string& dbLine) {
	User* output = new User();
	string buffer;
	size_t prevPosition;
	size_t position;

	position = dbLine.find(',');
	if (position == string::npos) {
		output = NULL;
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(0, position);
	try {
		output->setId(stoul(buffer));
	} catch (const char* e) {
		output = NULL;
		throw "Input line in the wrong format";
	}

	prevPosition = position + 1;
	position = dbLine.find(',', prevPosition);
	if (position == string::npos) {
		output = NULL;
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setPassword(buffer);

	prevPosition = position + 1;
	position = dbLine.find(',', prevPosition);
	if (position == string::npos) {
		output = NULL;
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setIsAdmin(to_bool(buffer));
	} catch (const char* e) {
		output = NULL;
		throw "Input line in the wrong format";
	}

	prevPosition = position + 1;
	position = dbLine.find(',', prevPosition);
	if (position == string::npos) {
		output = NULL;
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setName(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		output = NULL;
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setPhone(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		output = NULL;
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	output->setEmail(buffer);

	prevPosition = position + 1;
	position = dbLine.find(",", prevPosition);
	if (position == string::npos) {
		output = NULL;
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
		output = NULL;
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
		output = NULL;
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

void CentralControl::searchUserInDatabase(string& databaseString, size_t& initialPosition, size_t& finalPosition, unsigned long int id) {
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

bool CentralControl::isDatabaseClear() {
	string databaseString;
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}
	if (databaseString == "" || databaseString == "\n") {
		return true;
	}
	return false;
}

bool CentralControl::isUserCheckedin(unsigned long int id) {
	User* tempUser = (User*) activeUsers->search(id);
	if (tempUser == NULL) {
		return false;
	}
	return true;
}

bool CentralControl::canModifyDatabase(unsigned long int id) {
	User* tempUser = (User*) activeUsers->search(id);
	if (tempUser == NULL) {
		return false;
	}
	return tempUser->getIsAdmin();
}

void CentralControl::createUser(string inputUserString, string currentUserIdPass) {
	User* inputUser = new User();
	string databaseString;
	unsigned long int currentUserId;
	string currentUserPass;

	try {
		getUserIdPass(currentUserIdPass, currentUserId, currentUserPass);
	} catch (const char* e) {
		throw e;
	}

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

	// If the user isn't admin logged-in and the file is not empty, throw exception
	if (!canModifyDatabase(currentUserId)) {
		if (!(databaseString == "" || databaseString == "\n")) {
			delete inputUser;
			throw "No permission to create user";
		}
		if (!inputUser->getIsAdmin()) {
			delete inputUser;
			throw "First user isn't admin";
		}
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

string CentralControl::readUser(unsigned long int id) {
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

void CentralControl::updateUser(string inputUserString, string currentUserIdPass) {
	string databaseString;
	User* inputUser = new User();
	unsigned long int currentUserId;
	string currentUserPass;

	try {
		getUserIdPass(currentUserIdPass, currentUserId, currentUserPass);
	} catch (const char* e) {
		throw e;
	}

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

	// If the user isn't admin logged-in, throw exception
	if (!(canModifyDatabase(currentUserId) || (currentUserId == inputUser->getId()))) {
		delete inputUser;
		throw "No permission to update user";
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

	if (currentUserId == inputUser->getId()) {
		User* activeUser = (User*) activeUsers->search(inputUser->getId());
		if (activeUser != NULL) {
			activeUsers->update(inputUser);
		}
	}
}

void CentralControl::deleteUser(unsigned long int id, string currentUserIdPass) {
	string databaseString;
	unsigned long int currentUserId;
	string currentUserPass;

	try {
		getUserIdPass(currentUserIdPass, currentUserId, currentUserPass);
	} catch (const char* e) {
		throw e;
	}

	if (id == currentUserId) {
		throw "Can't delete current user";
	}

	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (char const* e) {
		throw e;
	}

	// If the user isn't admin logged-in, throw exception
	if (!canModifyDatabase(currentUserId)) {
		throw "No permission to delete user";
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

void CentralControl::checkin(string currentUserIdPass) {
	string databaseUser;
	unsigned long int currentUserId, dbUserId;
	string currentUserPass, dbUserPass;

	try {
		getUserIdPass(currentUserIdPass, currentUserId, currentUserPass);
	} catch (const char* e) {
		throw e;
	}

	try {
		databaseUser = readUser(currentUserId);
	} catch (const char* e) {
		throw e;
	}

	try {
		getUserIdPass(databaseUser, dbUserId, dbUserPass);
	} catch (const char* e) {
		throw e;
	}

	if (dbUserPass == currentUserPass) {
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

void CentralControl::checkout(string currentUserIdPass) {
	unsigned long int currentUserId;

	currentUserId = openDoor(currentUserIdPass);

	try {
		activeUsers->remove(currentUserId);
	} catch (const char* e) {
		throw e;
	}	
}

unsigned long int CentralControl::openDoor(string currentUserIdPass) {
	unsigned long int currentUserId;
	string currentUserPass;

	try {
		getUserIdPass(currentUserIdPass, currentUserId, currentUserPass);
	} catch (const char* e) {
		throw e;
	}

	if (!isUserCheckedin(currentUserId)) {
		throw "User not checked-in";
	}

	system("echo Door opened!\n");

	return currentUserId;
}

string CentralControl::getActiveUsers() {
	User* currentUser = NULL;
	size_t initialPosition = 0;
	size_t finalPosition;
	string allActiveUsers = "";
	unsigned long int currentUserId;

	string activeUsersId = activeUsers->listAll();
	if (activeUsersId.empty()) {
		return allActiveUsers;
	}

	while (true) {
		finalPosition = activeUsersId.find('\n', initialPosition);
		if (finalPosition == string::npos) {
			return allActiveUsers;
		}
		try {
			currentUserId = stoul(activeUsersId.substr(initialPosition, (finalPosition - initialPosition)));
		} catch (const char* e) {
			throw "Conversion from string to unsigned long int not valid";
		}
		currentUser = (User*) activeUsers->search(currentUserId);
		if (currentUser == NULL) {
			throw "Active Users list corrupted";
		}
		allActiveUsers += currentUser->toString();
		initialPosition = finalPosition + 1;
	}
}
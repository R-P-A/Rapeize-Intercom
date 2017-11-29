#include "centralControl.h"

CentralControl::CentralControl() {
	userDatabaseFileName = "userDatabase.csv";
	string databaseString;

	// Initialize database
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (const char* e) {
		throw e;
	}

	// Initialize GPIO
	system("sudo echo \"4\" > /sys/class/gpio/export");
	system("sudo echo \"out\" > /sys/class/gpio/gpio4/direction");
	system("sudo echo \"0\" > /sys/class/gpio/gpio4/value");
}

CentralControl::~CentralControl() {
	delete activeUsers;
}

User* CentralControl::stringToUser(string& dbLine) {
	User* output = new User();
	string buffer;
	size_t prevPosition;
	size_t position;

	// This function is divided in blocks. Each block finds the next value and save on the appropriate place.

	position = dbLine.find(',');
	if (position == string::npos) {
		output = NULL;
		throw "Input line in the wrong format";
	}
	buffer = dbLine.substr(0, position);
	try {
		output->setId(stoul(buffer));
	} catch (...) {
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
	} catch (const char* e) {
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
	} catch (const char* e) {
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
	} catch (const char* e) {
		throw e;
	}

	prevPosition = position + 1;
	position = dbLine.find("\n", prevPosition);
	buffer = dbLine.substr(prevPosition, position - prevPosition);
	try {
		output->setEndTime(buffer);
	} catch (const char* e) {
		throw e;
	}

	return output;
}

void CentralControl::searchUserInDatabase(string& databaseString, size_t& initialPosition, size_t& finalPosition, unsigned long int id) {
	string idString = to_string(id);
	initialPosition = 0;
	while (true) {
		// Seach in each line of the database for the user id.
		finalPosition = databaseString.find(",", initialPosition);
		if (idString == databaseString.substr(initialPosition, (finalPosition - initialPosition))) {
			finalPosition = databaseString.find("\n", initialPosition);
			return;
		}
		initialPosition = databaseString.find("\n", initialPosition);
		if (initialPosition == string::npos) {
			throw "User not found";
		}
		initialPosition++;
	}
}

bool CentralControl::isDatabaseClear() {
	string databaseString;
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (const char* e) {
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

void CentralControl::updateHTML() {
	string allActiveUsers;
	string htmlContent;
	string filename = "/var/www/html/index.html";
	size_t initialPosition, finalPosition;

	try {
		allActiveUsers = getActiveUsers();
	} catch (const char* e) {
		throw e;
		return;
	}

	try {
		readFile(htmlContent, filename);
	} catch (const char* e) {
		throw e;
		return;
	}
	initialPosition = 915;
	finalPosition = htmlContent.find("</pre>", initialPosition);
	if ((initialPosition == string::npos) || (finalPosition == string::npos)) {
		throw "HTML Corrupted";
	}
	htmlContent.replace(initialPosition, (finalPosition - initialPosition), allActiveUsers);

	try {
		writeFileClear(htmlContent, filename);
	} catch (const char* e) {
		throw e;
		return;
	}
}

void CentralControl::openDoorGPIO() {
	system("sudo echo \"1\" > /sys/class/gpio/gpio4/value");
	sleep(3);
	system("sudo echo \"0\" > /sys/class/gpio/gpio4/value");
}

bool CentralControl::canModifyDatabase(unsigned long int id) {
	User* tempUser = (User*) activeUsers->search(id);
	if (tempUser == NULL) {
		return false;
	}
	return tempUser->getIsAdmin();
}

void CentralControl::createUser(unsigned long int currentUserId, string inputUserString) {
	User* inputUser = NULL;
	string databaseString;

	try {
		inputUser = stringToUser(inputUserString);
	} catch (const char* e) {
		delete inputUser;
		throw e;
	}

	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (const char* e) {
		delete inputUser;
		throw e;
	}

	// If the user isn't admin checked-in.
	if (!canModifyDatabase(currentUserId)) {
		// If the file is not empty and the user isn't admin checked-in, throw exception.
		if (!(databaseString == "" || databaseString == "\n")) {
			delete inputUser;
			throw "No permission to create user";
		}
		// If the file is empty and the user to be created isn't admin, throw exception.
		if (!inputUser->getIsAdmin()) {
			delete inputUser;
			throw "First user isn't admin";
		}
	}

	size_t initialPosition, finalPosition;
	try {
		searchUserInDatabase(databaseString, initialPosition, finalPosition, inputUser->getId());
	} catch (const char* e) {
		try {
			writeFileAppend(inputUserString, userDatabaseFileName);
		} catch (const char* e) {
			delete inputUser;
			throw e;
		}
		delete inputUser;
		return;
	}
	delete inputUser;
	throw "User already exists";
}

string CentralControl::readUser(unsigned long int currentUserId, unsigned long int targetId) {
	string databaseString;
	string userString;

	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (const char* e) {
		throw e;
	}

	// If the user isn't admin checked-in and the target user isn't the user itself, throw exception.
	if ((!canModifyDatabase(currentUserId)) && (currentUserId != targetId)) {
		throw "No permission to read user";
	}

	size_t initialPosition, finalPosition;
	try {
		searchUserInDatabase(databaseString, initialPosition, finalPosition, targetId);
	} catch (const char* e) {
		throw e;
	}
	userString = databaseString.substr(initialPosition, (finalPosition - initialPosition + 1));
	
	return userString;
}

void CentralControl::updateUser(unsigned long int currentUserId, string inputUserString) {
	string databaseString;
	User* inputUser = NULL;

	try {
		inputUser = stringToUser(inputUserString);
	} catch (const char* e) {
		delete inputUser;
		throw e;
	}
	
	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (const char* e) {
		delete inputUser;
		throw e;
	}

	// If the user isn't admin checked-in and the target user isn't the user itself, throw exception.
	if ((!canModifyDatabase(currentUserId)) && (currentUserId != inputUser->getId())) {
		delete inputUser;
		throw "No permission to update user";
	}

	size_t initialPosition, finalPosition;
	try {
		searchUserInDatabase(databaseString, initialPosition, finalPosition, inputUser->getId());
	} catch (const char* e) {
		delete inputUser;
		throw e;
	}

	databaseString.replace(initialPosition, (finalPosition - initialPosition + 1), inputUserString);

	try {
		writeFileClear(databaseString, userDatabaseFileName);
	} catch (const char* e) {
		delete inputUser;
		throw e;
	}

	User* activeUser = (User*) activeUsers->search(inputUser->getId());
	if (activeUser != NULL) {
		activeUsers->update(inputUser);
		try {
			updateHTML();		
		} catch (const char* e) {
			throw e;
		}
	}
	
}

void CentralControl::deleteUser(unsigned long int currentUserId, unsigned long int targetId) {
	string databaseString;

	try {
		readFile(databaseString, userDatabaseFileName);
	} catch (const char* e) {
		throw e;
	}

	// If the user isn't admin checked-in and the target user isn't the user itself, throw exception.
	if ((!canModifyDatabase(currentUserId)) && (currentUserId != targetId)) {
		throw "No permission to delete user";
	}

	size_t initialPosition, finalPosition;
	try {
		searchUserInDatabase(databaseString, initialPosition, finalPosition, targetId);
	} catch (const char* e) {
		throw e;
	}
	
	databaseString.erase(initialPosition, (finalPosition - initialPosition + 1));

	try {
		writeFileClear(databaseString, userDatabaseFileName);
	} catch (const char* e) {
		throw e;
	}
}

unsigned int CentralControl::weekDayToNumber(string weekDay) {
	if (weekDay.compare("Sunday") == 0) {
		return 0;
	}
	if (weekDay.compare("Monday") == 0) {
		return 1;
	}
	if (weekDay.compare("Tuesday") == 0) {
		return 2;
	}
	if (weekDay.compare("Wednesday") == 0) {
		return 3;
	}
	if (weekDay.compare("Thursday") == 0) {
		return 4;
	}
	if (weekDay.compare("Friday") == 0) {
		return 5;
	}
	if (weekDay.compare("Saturday") == 0) {
		return 6;
	}

	throw "Wrong weekDay input";
}

unsigned long int CentralControl::timeStringToNumber(string timeString) {
	unsigned long int hour, min;
	size_t prevPosition, position;

	position = timeString.find(':');
	if (position == string::npos) {
		throw "Input line in the wrong format";
	}
	try {		
		hour = stoul(timeString.substr(0, position));
	} catch (...) {
		throw "Input line in the wrong format";		
	}

	prevPosition = position + 1;
	position = timeString.find('\n');
	try {		
		min = stoul(timeString.substr(prevPosition, position));
	} catch (...) {
		throw "Input line in the wrong format";		
	}

	return hour*3600 + min*60;
}

void CentralControl::checkin(unsigned long int currentUserId, string currentUserPass) {
	string databaseUser;
	unsigned long int beginTimeSecs, endTimeSecs, currentTimeSecs;
	unsigned int beginWeekDay, endWeekDay, currentWeekDay;

	try {
		databaseUser = readUser(currentUserId, currentUserId);
	} catch (const char* e) {
		throw e;
	}

	User* checkinUser = NULL;

	try {
		checkinUser = stringToUser(databaseUser);
	} catch (const char* e) {
		delete checkinUser;
		throw e;
	}

	try {
		beginWeekDay = weekDayToNumber(checkinUser->getBeginWeekDay());
		endWeekDay = weekDayToNumber(checkinUser->getEndWeekDay());
		beginTimeSecs = timeStringToNumber(checkinUser->getBeginTime());
		endTimeSecs = timeStringToNumber(checkinUser->getEndTime());
	} catch (const char* e) {
		delete checkinUser;
		throw e;
	}

	myTime.updateTimeDateInfo();
	currentTimeSecs = (unsigned) (myTime.getHour()*3600 + myTime.getMin()*60 + myTime.getSec());
	try {
		currentWeekDay = weekDayToNumber(myTime.getWeekDay());
	} catch (const char* e) {
		delete checkinUser;
		throw e;
	}

	if (currentUserPass != checkinUser->getPassword()) {
		delete checkinUser;
		throw "Password do not match";
	}

	if (currentTimeSecs < beginTimeSecs) {
		delete checkinUser;
		throw "Current time before beginning time";
	}

	if (currentTimeSecs > endTimeSecs) {
		delete checkinUser;
		throw "Current time after ending time";
	}

	if (currentWeekDay < beginWeekDay) {
		delete checkinUser;
		throw "Current day of the week before begin week day";
	}

	if (currentWeekDay > endWeekDay) {
		delete checkinUser;
		throw "Current day of the week after end week day";
	}

	thread (openDoorGPIO).detach();
		
	try {
		activeUsers->insert(checkinUser);
	} catch (const char* e) {
		delete checkinUser;
		throw e;
	}

	try {
		updateHTML();		
	} catch (const char* e) {
		throw e;
	}
}

void CentralControl::checkout(unsigned long int currentUserId) {
	thread (openDoorGPIO).detach();

	try {
		activeUsers->remove(currentUserId);
	} catch (const char* e) {
		throw e;
	}

	try {
		updateHTML();		
	} catch (const char* e) {
		throw e;
	}
}

void CentralControl::openDoor(unsigned long int currentUserId) {
	if (!isUserCheckedin(currentUserId)) {
		throw "User not checked-in";
	}

	thread (openDoorGPIO).detach();
}

string CentralControl::getActiveUsers() {
	User* currentUser = NULL;
	size_t initialPosition = 0;
	size_t finalPosition;
	string allActiveUsers = "";
	unsigned long int currentUserId;

	string activeUsersId = activeUsers->listAll();
	if (activeUsersId.empty()) {
		allActiveUsers += "\n";
		return allActiveUsers;
	}

	while (true) {
		finalPosition = activeUsersId.find('\n', initialPosition);
		if (finalPosition == string::npos) {
			return allActiveUsers;
		}
		try {
			currentUserId = stoul(activeUsersId.substr(initialPosition, (finalPosition - initialPosition)));
		} catch (...) {
			throw "Conversion from string to unsigned long int not valid";
		}
		currentUser = (User*) activeUsers->search(currentUserId);
		if (currentUser == NULL) {
			throw "Active Users list corrupted";
		}
		allActiveUsers += to_string(currentUser->getId()) + ",";
		allActiveUsers += currentUser->getName() + ",";
		allActiveUsers += currentUser->getPhone() + ",";
		allActiveUsers += currentUser->getEmail() + "\n";
		initialPosition = finalPosition + 1;
	}
}
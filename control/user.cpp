#include "user.h"

User::User() {
	id = 0;
	name = "";
	phone = "";
	email = "";
	allowedPeriod = "";
}

User::User(unsigned long int idInput, string nameInput, string phoneInput, string emailInput, string allowedPeriodInput) {

	setAllowedPeriod(allowedPeriodInput);

	id = idInput;
	name = nameInput;
	phone = phoneInput;
	email = emailInput;
}

string User::getName() {
	return name;
}

void User::setName(string value) {
	name = value;
}

string User::getPhone() {
	return phone;
}

void User::setPhone(string value) {
	phone = value;
}

string User::getEmail() {
	return email;
}

void User::setEmail(string value) {
	email = value;
}

string User::getAllowedPeriod() {
	return allowedPeriod;
}

void User::setAllowedPeriod(string value) {
	// If it's in the wrong format "W,W,hh:mm,hh:mm,", throw exception
	if ( value[0] > '6'   || value[0] < '0'  ||
		 value[1] != ','  ||
		 value[2] > '6'   || value[2] < '0'  ||
		 value[3] != ','  ||
		 value[4] > '2'   || value[4] < '0'  ||
		 (value[4] == '2' && value[5] > '3') ||		// Checks if hour is > 23
		 value[5] > '9'   || value[5] < '0'  ||
		 value[6] != ':'  ||
		 value[7] > '5'   || value[7] < '0'  ||
		 value[8] > '9'   || value[8] < '0'  ||
		 value[9] != ','  ||
		 value[10] > '2'  || value[10] < '0' ||
		 (value[10] == '2'&& value[11] > '3')||		// Checks if hour is > 23
		 value[11] > '9'  || value[11] < '0' ||
		 value[12] != ':' ||
		 value[13] > '5'  || value[13] < '0' ||
		 value[14] > '9'  || value[14] < '0' ||
		 value[15] != '\n' ) {
		throw "allowedPeriod in wrong format";
	}

	allowedPeriod = value;
}
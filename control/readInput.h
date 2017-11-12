#ifndef READINPUT
#define READINPUT

#include <iostream>
#include <string>

using namespace std;

string getString() {
	string input;
	// Get input in string format
	while (input.empty()) {
		getline(cin, input);
	}
	return input;
}

template <typename numberType>
bool readNumber(numberType& output) {
	string input = getString();
	output = 0;
	int i = 0;
	int signal = 1;

	if (input[0] == '-') {
		i = 1;
		signal = -1;
	}
	if (input[0] == '+') {
		i = 1;
		signal = 1;
	} 

	for (; (input[i] >= '0' && input[i] <= '9'); i++) {
		output = output*10 + input[i] - '0';
	}

	if (input[i] == '\0') {
		output *= signal;
		return true;
	}
	if (input[i] != '.') {
		output = 0;
		return false;
	}

	long decimal = 1;
	for (i++; (input[i] >= '0' && input[i] <= '9'); i++) {
		output = output*10 + input[i] - '0';
		decimal *= 10;
	}
	output /= (numberType) decimal;
	output *= signal;

	if ((unsigned) i == input.length()) {
		return true;
	}
	output = 0;
	return false;
}

bool readString(string& output) {
	output = getString();
	return true;
}

bool readChar(char& output) {
	string input = getString();
	if (input.length() == '1') {
		output = input[0];
		return true;
	}
	output = 0;
	return false;
}

#endif
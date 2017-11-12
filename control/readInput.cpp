#include "readInput.h"

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
template bool readNumber<int>(int& input);
template bool readNumber<short int>(short int& input);
template bool readNumber<long int>(long int& input);
template bool readNumber<long long int>(long long int& input);
template bool readNumber<unsigned int>(unsigned int& input);
template bool readNumber<unsigned short int>(unsigned short int& input);
template bool readNumber<unsigned long int>(unsigned long int& input);
template bool readNumber<unsigned long long int>(unsigned long long int& input);
template bool readNumber<float>(float& input);
template bool readNumber<double>(double& input);
template bool readNumber<long double>(long double& input);

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
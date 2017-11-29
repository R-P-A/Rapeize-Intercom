#include "myio.h"

bool to_bool(std::string const& s) {
	if (s.length() == 1) {
		return s != "0";
	} else {
		throw "Not a boolean value";
	}
}

void getStringLine(string& input, istream& stdInput) {
	// Get input in string format
	while (input.empty()) {
		getline(stdInput, input);
	}
	return;
}

void readFile(string& output, string fileName) {
	string input;
	ifstream inputFile(fileName.c_str());

	if (inputFile.is_open()) {
		input.assign((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));
		output = input;
		inputFile.close();
		return;
	}

	try {
		writeFileClear(input, fileName.c_str());
	} catch (char const* e) {
		throw "Couldn't open the file";
	}

	inputFile.open(fileName.c_str());
	if (inputFile.is_open()) {
		input.assign((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));
		inputFile.close();
	} else {
		throw "Couldn't open the file";
	}

	output = input;
	return;
}

void writeFileClear(string& input, string fileName) {
	ofstream outputFile(fileName.c_str());
	if (outputFile.is_open()) {
		outputFile << input;
		outputFile.close();
	} else {
		throw "Couldn't open the file";
	}
	return;
}

void writeFileAppend(string& input, string fileName) {
	ofstream outputFile(fileName.c_str(), fstream::app);
	if (outputFile.is_open()) {
		outputFile << input;
		outputFile.close();
	} else {
		throw "Couldn't open the file";
	}
	return;
}

void readString(string& output) {
	string input;
	getStringLine(input);
	output = input;
	return;
}

void readChar(char& output) {
	string input;
	getStringLine(input);

	// Check if the string contains only 1 character
	if (input.length() == 1) {
		output = input[0];
		return;
	}
	output = 0;
	throw "More than 1 character";
}
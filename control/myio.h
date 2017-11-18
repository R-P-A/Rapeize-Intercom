/** 
 *	@author  Rafael Pintar Alevato
 *	@date    11/11/2017
 *	@version 1.0 
 *	
 *	@brief Functions that read from the standard input.
 *
 */

#ifndef MYIO
#define MYIO

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

using namespace std;

/**
 *	Converts a string to bool.
 *	@param s String passed as reference to be checked.
 *	@return Whether is "1" or "0".
 */
bool to_bool(std::string const& s);

/**
 *	Function used internally to get a string in the standard input.
 *	@param input String passed as reference to be changed.
 *	@param std_input Define the standard input (cin, file)
 *	@return The string read.
 */
void getStringLine(string& input, istream& stdInput = cin);

/**
 *	Read the whole content of a file and saves on a string. If it doesn't exist, creates a new file with "".
 *	@param output The string to save the file read.
 *	@throw const char* "Couldn't open the file".
 */
void readFile(string& output, string fileName);
/**
 *	Clear a file and write the content given by a string.
 *	@param input The string to write in the file.
 *	@throw const char* "Couldn't open the file".
 */
void writeFileClear(string& input, string fileName);

/**
 *	Write the content given by a string in a file appending to the end.
 *	@param input The string to write in the file.
 *	@throw const char* "Couldn't open the file".
 */
void writeFileAppend(string& input, string fileName);

/**
 *	Read a signed number on the standard input.
 *	@tparam a signed number type (int, float, etc...).
 *	@param output The variable to save the number read.
 *	@throw const char* "Non numerical characters".
 */
template <typename numberType>
void readSignedNumber(numberType& output) {
	string input;
	getStringLine(input);
	output = 0;
	int i = 0;
	int signal = 1;

	// Check if number is negative or positive, walking on the string by 1 if there is the symbol.
	if (input[0] == '-') {
		i = 1;
		signal = -1;
	}
	if (input[0] == '+') {
		i = 1;
		signal = 1;
	} 

	// Walk through the string and saves each number on the integer part.
	for (; (input[i] >= '0' && input[i] <= '9'); i++) {
		output = output*10 + input[i] - '0';
	}

	// If it's the end of the string, there were only numbers, so input the signal and return.
	if (input[i] == '\0') {
		output *= signal;
		return;
	}
	// If there isn't a point and it isn't the end of the string, there are non numeric characters. Throw exception.
	if (input[i] != '.') {
		output = 0;
		throw "Non numerical characters";
	}

	// Calculating float value
	long decimal = 1;
	for (i++; (input[i] >= '0' && input[i] <= '9'); i++) {
		output = output*10 + input[i] - '0';
		decimal *= 10;
	}
	output /= (numberType) decimal;
	output *= signal;

	// If there were only numeric characters in the string.
	if ((unsigned) i == input.length()) {
		return;
	}
	output = 0;
	throw "Non numerical characters";
}

/**
 *	Read an unsigned number on the standard input.
 *	@tparam a unsigned number type (unsigned int, etc...).
 *	@param output The variable to save the number read.
 *	@throw const char* "Negative number not allowed".
 *	@throw const char* "Non numerical characters".
 */
template <typename numberType>
void readUnsignedNumber(numberType& output) {
	string input;
	getStringLine(input);
	output = 0;
	int i = 0;

	// Check if number is negative or positive, walking on the string by 1 if there is the symbol. Negative numbers return an exception.
	if (input[0] == '-') {
		throw "Negative number not allowed";
	}
	if (input[0] == '+') {
		i = 1;
	}

	// Walk through the string and saves each number on the integer part.
	for (; (input[i] >= '0' && input[i] <= '9'); i++) {
		output = output*10 + input[i] - '0';
	}

	// If it's the end of the string, there were only numbers, so return.
	if (input[i] == '\0') {
		return;
	}
	// Else, there were non numerical characters
	throw "Non numerical characters";
}

/**
 *	Read a string on the standard input.
 *	@param output The variable to save the string read.
 */
void readString(string& output);

/**
 *	Read a char on the standard input.
 *	@param output The variable to save the char read.
 *	@throw const char* "More than 1 character".
 */

void readChar(char& output);

#endif	// MYIO
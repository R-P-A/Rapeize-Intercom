#include <iostream>
#include "readInput.h"

using namespace std;

int main() {
	int tempInt;
	float tempFloat;
	unsigned long int tempULInt;
	char tempChar;
	string tempString;

	cout << "Please insert an int:" << endl;
	try {
		readSignedNumber<int>(tempInt);
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << "Int read: " << tempInt << endl << endl;

	cout << "Please insert a float:" << endl;
	try {
		readSignedNumber<float>(tempFloat);
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << "Float read: " << tempFloat << endl << endl;

	cout << "Please insert an unsigned long int:" << endl;
	try {
		readUnsignedNumber<unsigned long int>(tempULInt);
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << "Unsigned Long Int read: " << tempULInt << endl << endl;

	cout << "Please insert a char:" << endl;
	try {
		readChar(tempChar);
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << "Char read: " << tempChar << endl << endl;

	cout << "Please insert a string:" << endl;
	try {
		readString(tempString);
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << "String read: " << tempString << endl << endl;

	return 0;
}
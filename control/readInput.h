#ifndef READINPUT
#define READINPUT

#include <iostream>
#include <string>

using namespace std;

string getString();

template <typename numberType>
bool readNumber(numberType& output);

bool readString(string& output);

bool readChar(char& output);

#endif
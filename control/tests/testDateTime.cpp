#include <iostream>
#include "dateTime.h"

using namespace std;

int main() {
	DateTime tempDateTime;
	// getCurrentDateTime tests already all the other gets, since they call them in the functions
	cout << tempDateTime.getCurrentDateTime() << endl;
	return 0;
}
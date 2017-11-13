#include <iostream>
#include "user.h"
#include "model.h"

using namespace std;

int main() {
	User temp;

	cout << "Testing with valid values" << endl;
	try {
		temp = User(10, "Rafael", "99990989", "john@doe.com", "1,2,06:09,18:39,");
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << temp.getId() << endl;
	cout << temp.getName() << endl;
	cout << temp.getEmail() << endl;
	cout << temp.getPhone() << endl;
	cout << temp.getAllowedPeriod() << endl << endl;

	cout << "Testing with unvalid allowedPeriod (hour 24)" << endl;
	try {
		temp.setAllowedPeriod("1,2,06:00,24:00,");
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << temp.getAllowedPeriod() << endl << endl;

	cout << "Testing with unvalid allowedPeriod (no comma)" << endl;
	try {
		temp.setAllowedPeriod("1,206:00,24:00,");
	} catch (const char* e) {
		cout << e << endl;
	}
	cout << temp.getAllowedPeriod() << endl << endl;


	return 0;
}
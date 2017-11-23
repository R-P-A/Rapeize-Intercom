#include <iostream>
#include "serverSocket.h"
#include "centralControl.h"
#include "user.h"

using namespace std;

string callHandler(CentralControl* control, string& input);

int main() {
	CentralControl* control = new CentralControl();

	cout << "running....\n";
	try {
		// Create the socket
		ServerSocket server(8888);

		int i = 0;
		// This variable is just for testing, in the future this will be while(true)
		while (i < 8) {
			ServerSocket newSocket;
			server.accept(newSocket);
			cout << "Connected!\n";
			try {
				string input, output;
				newSocket >> input;
				output = callHandler(control, input);
				cout << "Returned: " << output << endl;
				newSocket << output;
			} catch (SocketException& e) {
				cout << "Socket exception was caught: " << e.description() << endl;
			}
			cout << endl;
			i++;
		}
	} catch (SocketException& e) {
		cout << "Exception was caught: " << e.description() << "\nExiting.\n";
	}

	delete control;

	return 0;
}

void getCommandIdPass(string& input, string& command, bool& isCheckedIn, unsigned long int& id, string& password) {
	size_t initialPosition, finalPosition;
	string buffer;
	
	finalPosition = input.find(',', 0);
	command = input.substr(0, finalPosition);
	if (finalPosition == string::npos) {
		throw "Missing isCheckedIn id and password";
	}

	initialPosition = finalPosition + 1;
	finalPosition = input.find(',', initialPosition);
	if (finalPosition == string::npos) {
		throw "Missing id and password";
	}
	buffer = input.substr(initialPosition, finalPosition - initialPosition);
	if (buffer == "1") {
		isCheckedIn = true;
	} else if (buffer == "0") {
		isCheckedIn = false;
	} else {
		throw "Wrong isCheckedIn input";
	}

	initialPosition = finalPosition + 1;
	finalPosition = input.find(',', initialPosition);
	if (finalPosition == string::npos) {
		throw "Missing password";
	}
	try {
		id = stoul(input.substr(initialPosition, finalPosition - initialPosition));
	} catch (...) {
		throw "Wrong id input";
	}

	initialPosition = finalPosition + 1;
	finalPosition = input.find(',', finalPosition);
	password = input.substr(initialPosition, finalPosition - initialPosition);
}

string callHandler(CentralControl* control, string& input) {
	
	string output, command, password;
	bool isCheckedIn = true;
	unsigned long int id;

	try {
		getCommandIdPass(input, command, isCheckedIn, id, password);
	} catch (const char* e) {
		output = e;
		return output;
	}

	if (command == "checkin") {
		cout << "Got checkin" << endl;
		try {
			control->checkin(id, password);
		} catch (const char* e) {
			if (strcmp(e, "Id already exists") == 0) {
				output = "Checked-in with success. Door opened.";
				cout << "User already is checked-in." << endl;
				return output;
			}
			output = e;
			return output;
		}
		output = "Checked-in with success. Door opened.";
		return output;
	}

	output = "Wrong command";
	return output;
}
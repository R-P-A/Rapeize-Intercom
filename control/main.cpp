#include <iostream>
#include "serverSocket.h"
#include "centralControl.h"
#include "user.h"

using namespace std;

// Functions declarations
string callHandler(CentralControl* control, string& input);
void getCommandIdPass(string& input, string& command, unsigned long int& id, string& password);
string checkinHandler(CentralControl* control, unsigned long int id, string& password);
string getActiveUsersHandler(CentralControl* control);
string checkoutHandler(CentralControl* control, unsigned long int id, string& password);

int main() {
	CentralControl* control = new CentralControl();

	cout << "running....\n";
	try {
		// Create the socket
		ServerSocket server(8888);

		int i = 0;
		// This variable is just for testing, in the future this will be while(true)
		while (i < 15) {
			ServerSocket newSocket;
			server.accept(newSocket);
			cout << "Connected!" << endl;
			try {
				string input, output;
				newSocket >> input;
				output = callHandler(control, input);
				cout << "Returned: " << output;
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

string callHandler(CentralControl* control, string& input) {
	
	string output, command, password;
	unsigned long int id;

	try {
		getCommandIdPass(input, command, id, password);
	} catch (const char* e) {
		output = e;
		output += "\n";
		return output;
	}

	if (command == "checkin") {
		cout << "Got checkin\n";
		output = checkinHandler(control, id, password);
		return output;
	}

	if (command == "getActiveUsers") {
		cout << "Got getActiveUsers\n";
		output = getActiveUsersHandler(control);
		return output;
	}

	if (command == "checkout") {
		cout << "Got checkout\n";
		output = checkoutHandler(control, id, password);
		return output;
	}

	output = "Wrong command\n";
	return output;
}

string checkinHandler(CentralControl* control, unsigned long int id, string& password) {
	string output;
	try {
		control->checkin(id, password);
	} catch (const char* e) {
		if (strcmp(e, "Id already exists") == 0) {
			output = "Checked-in with success\n";
			cout << "User already is checked-in\n";
			return output;
		}
		output = e;
		output += "\n";
		return output;
	}
	output = "Checked-in with success\n";
	return output;
}

string getActiveUsersHandler(CentralControl* control) {
	string output;
	try {
		output = control->getActiveUsers();
	} catch (const char* e) {
		output = e;
		output += "\n";
		return output;
	}
	return output;
}

string checkoutHandler(CentralControl* control, unsigned long int id, string& password) {
	string output;
	try {
		control->checkout(id);
	} catch (const char* e) {
		output = checkinHandler(control, id, password);
		if (output == "Checked-in with success\n") {
			try {
				control->checkout(id);
			} catch (const char* e) {
				output = e;
				output += "\n";
				return output;
			}
			output = "Checked-out with success\n";
			return output;
		}
		return output;
	}
	output = "Checked-out with success\n";
	return output;
}

void getCommandIdPass(string& input, string& command, unsigned long int& id, string& password) {
	size_t initialPosition, finalPosition;
	
	finalPosition = input.find(',', 0);
	command = input.substr(0, finalPosition);
	if (finalPosition == string::npos) {
		throw "Missing id and password";
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


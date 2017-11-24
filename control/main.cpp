#include <iostream>
#include "serverSocket.h"
#include "centralControl.h"
#include "user.h"

using namespace std;

// Functions declarations
string callHandler(CentralControl* control, string& input);
void getCommandIdPass(string& input, string& command, unsigned long int& id, string& password, string& newUserInput);
void checkinHandler(CentralControl* control, string& output, unsigned long int id, string& password);
void getActiveUsersHandler(CentralControl* control, string& output);
void checkoutHandler(CentralControl* control, string& output, unsigned long int id, string& password);
void openDoorHandler(CentralControl* control, string& output, unsigned long int id, string& password);
void createUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, string& newUserInput);
void updateUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, string& newUserInput);

int main() {
	CentralControl* control = new CentralControl();

	cout << "running....\n";
	try {
		// Create the socket
		ServerSocket server(8888);

		// This variable is just for testing, in the future this will be while(true)
		int i = 0;
		while (i < 52) {
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
	string output, command, password, newUserInput;
	unsigned long int id;

	try {
		getCommandIdPass(input, command, id, password, newUserInput);
	} catch (const char* e) {
		output = e;
		output += "\n";
		return output;
	}

	if (command == "checkin") {
		cout << "Got checkin\n";
		checkinHandler(control, output, id, password);
		return output;
	}

	if (command == "getActiveUsers") {
		cout << "Got getActiveUsers\n";
		getActiveUsersHandler(control, output);
		return output;
	}

	if (command == "checkout") {
		cout << "Got checkout\n";
		checkoutHandler(control, output, id, password);
		return output;
	}

	if (command == "openDoor") {
		cout << "Got openDoor\n";
		openDoorHandler(control, output, id, password);
		return output;
	}

	if (command == "createUser") {
		cout << "Got createUser\n";
		createUserHandler(control, output, id, password, newUserInput);
		return output;
	}

	if (command == "updateUser") {
		cout << "Got updateUser\n";
		updateUserHandler(control, output, id, password, newUserInput);
		return output;
	}

	output = "Wrong command\n";
	return output;
}

void checkinHandler(CentralControl* control, string& output, unsigned long int id, string& password) {
	try {
		control->checkin(id, password);
	} catch (const char* e) {
		if (strcmp(e, "Id already exists") == 0) {
			output = "Checked-in with success\n";
			cout << "User already is checked-in\n";
			return;
		}
		output = e;
		output += "\n";
		return;
	}
	output = "Checked-in with success\n";
	return;
}

void getActiveUsersHandler(CentralControl* control, string& output) {
	try {
		output = control->getActiveUsers();
	} catch (const char* e) {
		output = e;
		output += "\n";
		return;
	}
	return;
}

void checkoutHandler(CentralControl* control, string& output, unsigned long int id, string& password) {
	try {
		control->checkout(id);
	} catch (const char* e) {
		checkinHandler(control, output, id, password);
		if (output == "Checked-in with success\n") {
			try {
				control->checkout(id);
			} catch (const char* e) {
				output = e;
				output += "\n";
				return;
			}
			output = "Checked-out with success\n";
			return;
		}
		return;
	}
	output = "Checked-out with success\n";
	return;
}

void openDoorHandler(CentralControl* control, string& output, unsigned long int id, string& password) {
	try {
		control->openDoor(id);
	} catch (const char* e) {
		checkinHandler(control, output, id, password);
		if (output == "Checked-in with success\n") {
			try {
				control->openDoor(id);
			} catch (const char* e) {
				output = e;
				output += "\n";
				return;
			}
			output = "Door opened\n";
			return;
		}
		return;
	}
	output = "Door opened\n";
	return;
}

void createUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, string& newUserInput) {
	try {
		control->createUser(id, newUserInput);
	} catch (const char* e) {
		if (strcmp(e, "No permission to create user") == 0) {
			checkinHandler(control, output, id, password);
			if (output == "Checked-in with success\n") {
				try {
					control->createUser(id, newUserInput);
				} catch (const char* e) {
					output = e;
					output += "\n";
					return;
				}
				output = "User created\n";
			}
			return;
		}
		output = e;
		output += "\n";
		return;		
	}
	output = "User created\n";
	return;
}

void updateUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, string& newUserInput) {
	try {
		control->updateUser(id, newUserInput);
	} catch (const char* e) {
		if (strcmp(e, "No permission to update user") == 0) {
			checkinHandler(control, output, id, password);
			if (output == "Checked-in with success\n") {
				try {
					control->updateUser(id, newUserInput);
				} catch (const char* e) {
					output = e;
					output += "\n";
					return;
				}
				output = "User updated\n";
			}
			return;
		}
		output = e;
		output += "\n";
		return;		
	}
	output = "User updated\n";
	return;
}

void getCommandIdPass(string& input, string& command, unsigned long int& id, string& password, string& newUserInput) {
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
	finalPosition = input.find(',', initialPosition);
	password = input.substr(initialPosition, finalPosition - initialPosition);
	if (finalPosition == string::npos) {
		return;
	}

	initialPosition = finalPosition + 1;
	finalPosition = input.find('\n', initialPosition);
	newUserInput = input.substr(initialPosition, finalPosition - initialPosition);
	newUserInput += "\n";
}

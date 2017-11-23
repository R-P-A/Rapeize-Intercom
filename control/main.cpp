#include <iostream>
#include "serverSocket.h"
#include "centralControl.h"
#include "user.h"

using namespace std;

string callResponse(CentralControl* control, string& input);

int main() {
	CentralControl* control = new CentralControl();

	cout << "running....\n";
	try {
		// Create the socket
		ServerSocket server(8888);

		// while (true) {
			ServerSocket newSocket;
			server.accept(newSocket);
			cout << "Connected!\n";
			try {
				string input, output;
				newSocket >> input;
				output = callResponse(control, input);
				cout << output << endl;
				newSocket << output;
			} catch (SocketException& e) {
				cout << "Exception was caught: " << e.description() << "\nExiting.\n";
			}
			cout << endl;
		// }
	} catch (SocketException& e) {
		cout << "Exception was caught: " << e.description() << "\nExiting.\n";
	}

	delete control;

	return 0;
}

void getCommandIdPass(string& input, string& command, unsigned long int& id, string& password) {
	size_t position, finalPosition;
	
	position = input.find(',', 0);
	command = input.substr(0, position);
	if (position == string::npos) {
		throw "Missing id and password";
	}
	position++;
	finalPosition = input.find(',', position);
	if (finalPosition == string::npos) {
		throw "Missing password";
	}
	try {
		id = stoul(input.substr(position, finalPosition - position));
	} catch (...) {
		throw "Wrong id input";
	}
	finalPosition++;
	finalPosition = input.find(',', finalPosition);
	password = input.substr(position, finalPosition - position);
}

string callResponse(CentralControl* control, string& input) {
	
	string output, command, password;
	unsigned long int id;

	try {
		getCommandIdPass(input, command, id, password);
	} catch (const char* e) {
		output = e;
		cout << "Returned exception: " << output << endl;
		return output;
	}

	if (command.compare("checkin") == 0) {
		cout << "Got checkin" << endl;

		try {
			control->checkin(password);
		} catch (const char* e) {
			output = e;
			cout << "Returned exception: " << output << endl;
			return output;
		}
		output = "Checked-in with success. Door opened.";
		return output;
	}

	// if (buffer.compare("isDa1tabaseClear") == 0) {
	// 	cout << "Got isDatabaseClear" << endl;
	// 	if (control->isDatabaseClear()) {
	// 		output = "true";
	// 		return output;
	// 	}
	// 	output = "false";
	// 	cout << "Returned: " << output << endl;
	// 	return output;
	// }

	// if (buffer.compare("isUserCheckedin") == 0) {
	// 	cout << "Got isUserCheckedin" << endl;
	// 	if (position == string::npos) {
	// 		output = "Missing id";
	// 		cout << "Returned: " << output << endl;
	// 		return output;
	// 	}
	// 	prevPosition = position + 1;
	// 	position = input.find(',', prevPosition);
	// 	try {
	// 		id = stoul(input.substr(prevPosition, position - prevPosition));
	// 	} catch (...) {
	// 		output = "Wrong id input";
	// 		cout << "Returned exception: " << output << endl;
	// 		return output;			
	// 	}

	// 	if (control->isUserCheckedin(id)) {
	// 		output = "true";
	// 		return output;
	// 	}
	// 	output = "false";
	// 	cout << "Returned: " << output << endl;
	// 	return output;
	// }

	// if (buffer.compare("canModifyDatabase") == 0) {
	// 	cout << "Got isUserCheckedin" << endl;
	// 	if (position == string::npos) {
	// 		output = "Missing id";
	// 		cout << "Returned: " << output << endl;
	// 		return output;
	// 	}
	// 	prevPosition = position + 1;
	// 	position = input.find(',', prevPosition);
	// 	try {
	// 		id = stoul(input.substr(prevPosition, position - prevPosition));
	// 	} catch (...) {
	// 		output = "Wrong id input";
	// 		cout << "Returned exception: " << output << endl;
	// 		return output;			
	// 	}

	// 	if (control->canModifyDatabase(id)) {
	// 		output = "true";
	// 		return output;
	// 	}
	// 	output = "false";
	// 	cout << "Returned: " << output << endl;
	// 	return output;
	// }

	// inputUserPass = inputUserIdPass.substr(prevPosition, position - prevPosition);
	// control->getUserIdPass(input, id, pass);
	output = "Wrong command";
	return output;
}
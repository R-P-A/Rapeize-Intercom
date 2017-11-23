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

string callResponse(CentralControl* control, string& input) {
	
	string command, output;
	size_t position, prevPosition;
	
	position = input.find(',', 0);
	command = input.substr(0, position);

	if (command.compare("isDatabaseClear") == 0) {
		cout << "Got isDatabaseClear" << endl;
		if (control->isDatabaseClear()) {
			output = "true";
			return output;
		}
		output = "false";
		cout << "Returned " << output << endl;
		return output;
	}


	// inputUserPass = inputUserIdPass.substr(prevPosition, position - prevPosition);
	// control->getUserIdPass(input, id, pass);
	output = "Wrong command";
	return output;
}
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include "clientSocket.h"
#include "socketException.h"

using namespace std;

void callServer(string& input) {
	int i = 0;
	while (i < 10) {
		try {
			ClientSocket client_socket("192.168.1.95", 8888);
			string reply;
			client_socket << input;
			client_socket >> reply;
			cout << "Server Response:" << endl << reply << endl << endl;
			i = 11;
		}
		catch(SocketException& e) {
			cout << "Exception was caught:" << e.description() << "\n";
			i++;
		}
		usleep(500000);
	}
}

int main() {
	string input;

	cout << endl << "Try to call with input missing isCheckedIn, id and password" << endl;
	input = "cheasd";
	callServer(input);

	cout << endl << "Try to call with input missing id and password" << endl;
	input = "cheasd,0";
	callServer(input);

	cout << endl << "Try to call with input missing password" << endl;
	input = "cheasd,0,10";
	callServer(input);

	cout << endl << "Try to call with non-existing command" << endl;
	input = "cheasd,0,10,asd";
	callServer(input);

	cout << endl << "Try to checkin with non-existing user" << endl;
	input = "checkin,0,10,asd";
	callServer(input);

	cout << endl << "Try to checkin with wrong password" << endl;
	input = "checkin,0,487,pas";
	callServer(input);

	cout << endl << "Checkin with user 487 successfully" << endl;
	input = "checkin,0,487,pass";
	callServer(input);

	cout << endl << "Try to checkin with already checked-in user" << endl;
	input = "checkin,1,487,pass";
	callServer(input);

	return 0;
}

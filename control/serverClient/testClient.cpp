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
			cout << "Server Response:" << endl << reply << endl;
			i = 11;
		}
		catch(SocketException& e) {
			cout << "Exception was caught: " << e.description() << endl;
			i++;
		}
		usleep(500000);
	}
}

int main() {
	string input;

	cout << "Try to call with input missing id and password" << endl;
	input = "cheasd";
	callServer(input);

	cout << "Try to call with input missing password" << endl;
	input = "cheasd,48";
	callServer(input);

	cout << "Try to call with non-existing command" << endl;
	input = "cheasd,48,asd";
	callServer(input);

	cout << "Try to checkin with non-existing user" << endl;
	input = "checkin,48,asd";
	callServer(input);

	cout << "Try to checkin with wrong password" << endl;
	input = "checkin,487,pas";
	callServer(input);

	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers,487,pass";
	callServer(input);

	cout << "Checkout successfully with user 487 before checking in (in case of server failure)" << endl;
	input = "checkout,487,pass";
	callServer(input);

	cout << "Try to checkout with user 487 before checking in (in case of server failure) with non-existing id" << endl;
	input = "checkout,48,pass";
	callServer(input);

	cout << "Try to checkout with user 487 before checking in (in case of server failure) with wrong password" << endl;
	input = "checkout,487,pas";
	callServer(input);

	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers,487,pass";
	callServer(input);

	cout << "Open door successfully with user 487 before checking in (in case of server failure)" << endl;
	input = "openDoor,487,pass";
	callServer(input);

	cout << "Get all users successfully. The list has user 487." << endl;
	input = "getActiveUsers,487,pass";
	callServer(input);

	cout << "Checkout successfully with user 487 before checking in (in case of server failure)" << endl;
	input = "checkout,487,pass";
	callServer(input);

	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers,487,pass";
	callServer(input);

	cout << "Try to open door with user 487 before checking in (in case of server failure) with non-existing id" << endl;
	input = "checkout,48,pass";
	callServer(input);

	cout << "Try to open door with user 487 before checking in (in case of server failure) with wrong password" << endl;
	input = "checkout,487,pas";
	callServer(input);

	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers,487,pass";
	callServer(input);

	cout << "Checkin successfully with user 487" << endl;
	input = "checkin,487,pass";
	callServer(input);

	cout << "Checkin successfully with already checked-in user 487" << endl;
	input = "checkin,487,pass";
	callServer(input);

	cout << "Open door successfully with user 487" << endl;
	input = "openDoor,487,pass";
	callServer(input);

	cout << "Get all users successfully. The list has user 487." << endl;
	input = "getActiveUsers,487,pass";
	callServer(input);

	cout << "Checkout successfully with user 487" << endl;
	input = "checkout,487,pass";
	callServer(input);

	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers,487,pass";
	callServer(input);

	return 0;
}

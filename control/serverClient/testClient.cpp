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
			ClientSocket client_socket("192.168.1.5", 8888);
			string reply;
			client_socket << input;
			client_socket >> reply;
			cout << "Server Response:" << endl << reply;
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
	system("rm ../userDatabase.csv");

	string input;

	cout << endl << "------------------ Call with wrong inputs ------------------" << endl;
	cout << "Try to call with input missing id and password" << endl;
	input = "cheasd";
	callServer(input);
	cout << "Try to call with input missing password" << endl;
	input = "cheasd,48";
	callServer(input);
	cout << "Try to call with non-existing command" << endl;
	input = "cheasd,48,asd";
	callServer(input);

	cout << endl << "-------------------- Create user block ---------------------" << endl;
	cout << "Try to create first user 487 with wrong id format" << endl;
	input = "createUser,487,pass,a487,pass,1,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
	callServer(input);
	cout << "Try to create first user 487 with wrong week day format" << endl;
	input = "createUser,487,pass,487,pass,1,John,1010,john@doe.com,Monaday,Friday,08:30,23:30\n";
	callServer(input);
	cout << "Try to create first user 487 with wrong time format" << endl;
	input = "createUser,487,pass,487,pass,1,John,1010,john@doe.com,Monaday,Friday,24:30,23:30\n";
	callServer(input);
	cout << "Try to create first user 487 with missing inputs" << endl;
	input = "createUser,487,pass,487,pass,1,John,1010,john@doe.com,Monaday,Friday,08:30\n";
	callServer(input);
	cout << "Try to create first user 487 which isn't admin" << endl;
	input = "createUser,487,pass,487,pass,0,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
	callServer(input);
	cout << "Create successfully first user 487" << endl;
	input = "createUser,487,pass,487,pass,1,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
	callServer(input);
	cout << "Try to create user 487 already exists" << endl;
	input = "createUser,487,pass,487,pass,1,John,1010,john@doe.com,Monday,Friday,08:30,23:30\n";
	callServer(input);
	cout << "Create successfully user 123 which isn't admin" << endl;
	input = "createUser,487,pass,123,456,0,Rafael,1010,rafael@alevato.com,Monday,Friday,08:30,23:30\n";
	callServer(input);
	cout << "Try to create user 456 with user 123 which isn't admin" << endl;
	input = "createUser,123,456,456,456,0,Ruan,1010,ruan@molgero.com,Monday,Friday,08:30,23:30\n";
	callServer(input);
	cout << "Get all users successfully. The list is 123 and 487." << endl;
	input = "getActiveUsers,487,pass";
	callServer(input);

	cout << endl << "---------------------- Checkin block -----------------------" << endl;
	cout << "Checkout successfully with user 487" << endl;
	input = "checkout,487,pass";
	callServer(input);
	cout << "Checkout successfully with user 123" << endl;
	input = "checkout,123,456";
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
	cout << "Checkin successfully with user 487" << endl;
	input = "checkin,487,pass";
	callServer(input);
	cout << "Checkin successfully with already checked-in user 487" << endl;
	input = "checkin,487,pass";
	callServer(input);
	cout << "Get all users successfully. The list has user 487." << endl;
	input = "getActiveUsers,487,pass";
	callServer(input);
	
	cout << endl << "---------------------- Checkout block ----------------------" << endl;
	cout << "Checkout successfully with user 487" << endl;
	input = "checkout,487,pass";
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

	cout << endl << "--------------------- Open door block ----------------------" << endl;
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
	cout << "Open door successfully with user 487" << endl;
	input = "openDoor,487,pass";
	callServer(input);
	cout << "Get all users successfully. The list has user 487." << endl;
	input = "getActiveUsers,487,pass";
	callServer(input);

	return 0;
}

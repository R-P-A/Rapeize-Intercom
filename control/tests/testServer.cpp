#include <iostream>
#include <string>
#include <unistd.h>
#include "serverSocket.h"
#include "socketException.h"

using namespace std;

void callResponse(ServerSocket newSock) {
	try {
		string data;
		string temp = "Hello World!";
		newSock >> data;
		sleep(5);
		cout << data << endl << endl;
		newSock << temp;
	} catch (SocketException& e) {
		cout << "Exception was caught: " << e.description() << "\nExiting.\n";
	}
}

int main ()
{
	cout << "running....\n";
	try {
		// Create the socket
		ServerSocket server(8888);

		while (true) {
			ServerSocket newSock;
			server.accept(newSock);
			cout << "Connected!\n";
			// To Do
			callResponse(newSock);
		}
	} catch (SocketException& e) {
		cout << "Exception was caught: " << e.description() << "\nExiting.\n";
	}

	return 0;
}

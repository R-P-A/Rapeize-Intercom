#include <iostream>
#include <string>
#include <thread>
#include "serverSocket.h"
#include "socketException.h"

using namespace std;

void callResponse(ServerSocket newSock) {
	try {
		string data;
		string temp = "Hello World!";
		newSock >> data;
		cout << data << endl;
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


			cout << "Starting Thread!\n";
			// To Do
			callResponse(newSock);
			cout << "Finished Thread!\n\n";
		}
	} catch (SocketException& e) {
		cout << "Exception was caught: " << e.description() << "\nExiting.\n";
	}

	return 0;
}

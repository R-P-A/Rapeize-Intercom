#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include "clientSocket.h"
#include "socketException.h"

using namespace std;

int main() {
	int i = 0;
	while (i < 10) {
		try {
			ClientSocket client_socket("192.168.1.95", 8888);
			string reply;
			client_socket << "Test message.";
			client_socket >> reply;
			cout << "We received this response from the server:\n\"" << reply << "\"\n";
			i = 11;
		}
		catch(SocketException& e) {
			cout << "Exception was caught:" << e.description() << "\n";
			i++;
		}
		usleep(500000);
	}
	return 0;
}

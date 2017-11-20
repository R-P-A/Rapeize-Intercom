#include <iostream>
#include <string>
#include <thread>
#include "clientSocket.h"
#include "socketException.h"

using namespace std;

int main() {
    try {
        ClientSocket client_socket("192.168.1.95", 8888);
        string reply;

        try {
	       client_socket << "Test message.";
	       client_socket >> reply;
	    } catch(SocketException&) {}

        cout << "We received this response from the server:\n\"" << reply << "\"\n";;
    }
    catch(SocketException& e) {
        cout << "Exception was caught:" << e.description() << "\n";
    }

    return 0;
}
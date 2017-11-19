#include "serverSocket.h"
#include "socketException.h"
#include <string>

using namespace std;

int main ()
{
	cout << "running....\n";
	try {
		// Create the socket
		ServerSocket server(8888);

		while (true) {
			ServerSocket new_sock;
			server.accept(new_sock);
			cout << "Connected!\n";

			try {
				string data;
				string temp = "Hello World!";
				new_sock >> data;
				cout << data << endl;
				new_sock << temp;
			} catch (SocketException& e) {
				cout << "Exception was caught: " << e.description() << "\nExiting.\n";
			}
		}
	} catch (SocketException& e) {
		cout << "Exception was caught: " << e.description() << "\nExiting.\n";
	}
	return 0;
}

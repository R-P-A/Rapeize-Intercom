/** 
 *	@author  Rafael Pintar Alevato
 *	@date    23/11/2017
 *	@version 1.0 
 *	
 *	Before running this test, please set the while(true) on server to while(i<74) and increase i for each call.
 *	This way the CentralControl will be deleted.
 *
 */

#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <ctime>
#include "clientSocket.h"
#include "socketException.h"

using namespace std;

void callServer(string& input) {
	int i = 0;
	while (i < 10) {
		try {
			ClientSocket client_socket("192.168.1.170", 8888);
			string reply;
			client_socket << input;
			client_socket >> reply;
			cout << "Server Response:" << endl << reply << endl;
			i = 11;
		}
		catch(SocketException& e) {
			cout << "Exception was caught: " << e.description() << endl;
			i++;
			usleep(500000);
		}
	}
}

int main() {
	system("rm -f ../userDatabase.csv");

	string input;
	clock_t clocks = clock();

	cout << endl << "------------------ Call with wrong inputs ------------------" << endl;
	cout << "Try to call with input missing id and password" << endl;
	input = "cheasd\n";
	callServer(input);
	cout << "Try to call with input missing password" << endl;
	input = "cheasd,48\n";
	callServer(input);
	cout << "Try to call with non-existing command" << endl;
	input = "cheasd,48,asd\n";
	callServer(input);
	cout << "------------------------------------------------------------" << endl << endl;

	cout << endl << "-------------------- Create user block ---------------------" << endl;
	cout << "Try to create first user 487 with wrong id format" << endl;
	input = "createUser,487,pass,a487,pass,1,John,+554898888-8888,john@doe.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Try to create first user 487 with wrong week day format" << endl;
	input = "createUser,487,pass,487,pass,1,John,+554898888-8888,john@doe.com,Monaday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Try to create first user 487 with wrong time format" << endl;
	input = "createUser,487,pass,487,pass,1,John,+554898888-8888,john@doe.com,Monday,Saturday,24:30,23:30\n";
	callServer(input);
	cout << "Try to create first user 487 with missing inputs" << endl;
	input = "createUser,487,pass,487,pass,1,John,+554898888-8888,john@doe.com,Sunday,Saturday,08:30\n";
	callServer(input);
	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Try to create first user 487 which isn't admin" << endl;
	input = "createUser,487,pass,487,pass,0,John,+554898888-8888,john@doe.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Create successfully first user 487" << endl;
	input = "createUser,487,pass,487,pass,1,John,+554898888-8888,john@doe.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Try to create user 487 which already exists with user 487 before checking in (in case of server failure)" << endl;
	input = "createUser,487,pass,487,pass,1,John,+554898888-8888,john@doe.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Create successfully user 123 which isn't admin" << endl;
	input = "createUser,487,pass,123,456,0,Rafael,+554898888-8888,rafael@alevato.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Try to create user 456 with user 123 which isn't admin before checking in (in case of server failure)" << endl;
	input = "createUser,123,456,456,456,0,Ruan,+554898888-8888,ruan@molgero.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Get all users successfully. The list is 123 and 487." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Checkout successfully with user 487" << endl;
	input = "checkout,487,pass\n";
	callServer(input);
	cout << "Checkout successfully with user 123" << endl;
	input = "checkout,123,456\n";
	callServer(input);
	cout << "------------------------------------------------------------" << endl << endl;

	cout << endl << "--------------------- Read user block ----------------------" << endl;
	cout << "Read user 487 successfully with user 487 before checking in (in case of server failure)" << endl;
	input = "readUser,487,pass,487\n";
	callServer(input);
	cout << "Read user 123 successfully with user 487" << endl;
	input = "readUser,487,pass,123\n";
	callServer(input);
	cout << "Try to read user 837 which doesn't exist with user 487" << endl;
	input = "readUser,487,pass,837\n";
	callServer(input);
	cout << "Try to read user 487 with user 123 which isn't admin before checking in (in case of server failure)" << endl;
	input = "readUser,123,456,487\n";
	callServer(input);
	cout << "Read user 123 successfully with user 123 which isn't admin" << endl;
	input = "readUser,123,456,123\n";
	callServer(input);
	cout << "Get all users successfully. The list is 123 and 487." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Checkout successfully with user 487" << endl;
	input = "checkout,487,pass\n";
	callServer(input);
	cout << "Checkout successfully with user 123" << endl;
	input = "checkout,123,456\n";
	callServer(input);
	cout << "------------------------------------------------------------" << endl << endl;

	cout << endl << "-------------------- Update user block ---------------------" << endl;
	cout << "Try to update user 487 with wrong id format" << endl;
	input = "updateUser,487,pass,a487,pass,1,John,+554898888-8888,john@doe.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Try to update user 487 with wrong week day format" << endl;
	input = "updateUser,487,pass,487,pass,1,John,+554898888-8888,john@doe.com,Monaday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Try to update user 487 with wrong time format" << endl;
	input = "updateUser,487,pass,487,pass,1,John,+554898888-8888,john@doe.com,Sunday,Saturday,24:30,23:30\n";
	callServer(input);
	cout << "Try to update user 487 with missing inputs" << endl;
	input = "updateUser,487,pass,487,pass,1,John,+554898888-8888,john@doe.com,Sunday,Saturday,08:30\n";
	callServer(input);
	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Update user 487 successfully with user 487 before checking in (in case of server failure)" << endl;
	input = "updateUser,487,pass,487,pass,1,Ruan,+554898888-8888,ruan@molgero.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Try to update user 837 which doesn't exist with user 487" << endl;
	input = "updateUser,487,pass,837,pass,0,Ruan,+554898888-8888,ruan@molgero.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Try to update user 487 with user 123 which isn't admin before checking in (in case of server failure)" << endl;
	input = "updateUser,123,456,487,pass,1,Error,+554898888-8888,error@molgero.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Update user 123 successfully with user 123 which isn't admin" << endl;
	input = "updateUser,123,456,123,456,0,Kupas,+554898888-8888,ygor@kupas.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Get all users successfully. The list is 123 and 487." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Update user 123 successfully with user 487" << endl;
	input = "updateUser,487,pass,123,456,0,Rafael,+554898888-8888,rafael@alevato.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Get all users successfully. The list is 123 and 487." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Checkout successfully with user 487" << endl;
	input = "checkout,487,pass\n";
	callServer(input);
	cout << "Checkout successfully with user 123" << endl;
	input = "checkout,123,456\n";
	callServer(input);
	cout << "------------------------------------------------------------" << endl << endl;

	cout << endl << "---------------------- Checkin block -----------------------" << endl;
	cout << "Try to checkin with non-existing user" << endl;
	input = "checkin,48,asd\n";
	callServer(input);
	cout << "Try to checkin with wrong password" << endl;
	input = "checkin,487,pas\n";
	callServer(input);
	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Checkin successfully with user 487" << endl;
	input = "checkin,487,pass\n";
	callServer(input);
	cout << "Checkin successfully with already checked-in user 487" << endl;
	input = "checkin,487,pass\n";
	callServer(input);
	cout << "Checkin successfully with user 123" << endl;
	input = "checkin,123,456\n";
	callServer(input);
	cout << "Get all users successfully. The list has user 123 and 487." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "------------------------------------------------------------" << endl << endl;
	
	cout << endl << "---------------------- Checkout block ----------------------" << endl;
	cout << "Checkout successfully with user 487" << endl;
	input = "checkout,487,pass\n";
	callServer(input);
	cout << "Checkout successfully with user 123" << endl;
	input = "checkout,123,456\n";
	callServer(input);
	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Checkout successfully with user 487 before checking in (in case of server failure)" << endl;
	input = "checkout,487,pass\n";
	callServer(input);
	cout << "Try to checkout with user 487 before checking in (in case of server failure) with non-existing id" << endl;
	input = "checkout,48,pass\n";
	callServer(input);
	cout << "Try to checkout with user 487 before checking in (in case of server failure) with wrong password" << endl;
	input = "checkout,487,pas\n";
	callServer(input);
	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "------------------------------------------------------------" << endl << endl;

	cout << endl << "--------------------- Open door block ----------------------" << endl;
	cout << "Open door successfully with user 487 before checking in (in case of server failure)" << endl;
	input = "openDoor,487,pass\n";
	callServer(input);
	cout << "Get all users successfully. The list has user 487." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Checkout successfully with user 487" << endl;
	input = "checkout,487,pass\n";
	callServer(input);
	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Try to open door with non-existing user before checking in (in case of server failure) with non-existing id" << endl;
	input = "checkout,48,pass\n";
	callServer(input);
	cout << "Try to open door with user 487 before checking in (in case of server failure) with wrong password" << endl;
	input = "checkout,487,pas\n";
	callServer(input);
	cout << "Get all users successfully. The list is empty." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Checkin successfully with user 487" << endl;
	input = "checkin,487,pass\n";
	callServer(input);
	cout << "Open door successfully with user 487" << endl;
	input = "openDoor,487,pass\n";
	callServer(input);
	cout << "Get all users successfully. The list has user 487." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Checkout successfully with user 487" << endl;
	input = "checkout,487,pass\n";
	callServer(input);
	cout << "------------------------------------------------------------" << endl << endl;

	cout << endl << "-------------------- Delete user block ---------------------" << endl;
	cout << "Try to delete user 837 which doesn't exist with user 487 before checking in (in case of server failure)" << endl;
	input = "deleteUser,487,pass,837\n";
	callServer(input);
	cout << "Try to delete user 487 with user 123 which isn't admin before checking in (in case of server failure)" << endl;
	input = "deleteUser,123,456,487\n";
	callServer(input);
	cout << "Get all users successfully. The list has user 123 and 487." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Delete user 123 successfully with user 487" << endl;
	input = "deleteUser,487,pass,123\n";
	callServer(input);
	cout << "Checkout successfully with user 123" << endl;
	input = "checkout,123,456\n";
	callServer(input);
	cout << "Try to checkin with user 123. This will fail because user don't exist anymore" << endl;
	input = "checkin,123,456\n";
	callServer(input);
	cout << "Get all users successfully. The list has user 487." << endl;
	input = "getActiveUsers\n";
	callServer(input);
	cout << "Create successfully user 123 again" << endl;
	input = "createUser,487,pass,123,456,0,Rafael,+554898888-8888,rafael@alevato.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "Delete user 123 successfully with user 123" << endl;
	input = "deleteUser,123,456,123\n";
	callServer(input);
	cout << "Delete user 487 successfully with user 487" << endl;
	input = "deleteUser,487,pass,487\n";
	callServer(input);
	cout << "Create successfully first user 487 again" << endl;
	input = "createUser,487,pass,487,pass,1,John,+554898888-8888,john@doe.com,Sunday,Saturday,08:30,23:30\n";
	callServer(input);
	cout << "------------------------------------------------------------" << endl << endl;

	clocks = clock() - clocks;
	cout << "Total test runtime: " << (float) clocks / CLOCKS_PER_SEC << " s" << endl << endl;

	return 0;
}

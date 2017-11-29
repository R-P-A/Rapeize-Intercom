/** 
 *	@author  Rafael Pintar Alevato
 *	@date    23/11/2017
 *	@version 1.0 
 *	
 *	@brief Control that manages the lan socket for communicating the central control
 *	of the database and active user with other systems.
 *
 *	@section DESCRIPTION
 *	
 *	The socket always waits for an input and returns something on each accept.
 *
 *	Possible outputs for the caller:
 *	- wrong input:
 *		- "Missing id and password and not getActiveUsers"
 *		- "Missing password and not getActiveUsers"
 *		- "Wrong id input"
 *	- checkin:
 *		- "Checked-in with success,admin"
 *		- "Checked-in with success,user"
 *		- "Couldn't open the file"
 *		- "User not found"
 *		- "Password do not match"
 *		- "Wrong weekDay input"
 *		- "Current time before beginning time"
 *		- "Current time after ending time"
 *		- "Current day of the week before begin week day"
 *		- "Current day of the week after end week day"
 *	- getActiveUsers:
 *		- Active user in the following format: "id,pass,name,phone,email"
 *		- "Active Users list corrupted"
 *	- checkout:
 *		- "Checked-out with success"
 *		- "Id not found"
 *		- checkin possible outputs
 *	- openDoor:
 *		- "Door opened"
 *		- "User not checked-in"
 *		- checkin possible outputs
 *	- createUser:
 *		- "No permission to create user"
 *		- "First user isn't admin"
 *		- "User already exists"
 *		- "User created"
 *		- checkin possible outputs
 *	- readUser:
 *		- The user in the format "id,password,isAdmin,name,phone,email,beginWeekDay,endWeekDay,beginTime,endTime"
 *		- "No permission to read user"
 *		- "User not found"
 *		- checkin possible outputs
 *	- updateUser:
 *		- "User updated"
 *		- "No permission to update user"
 *		- "User not found"
 *		- checkin possible outputs
 *	- deleteUser:
 *		- "User deleted"
 *		- "No permission to delete user"
 *		- "User not found"
 *		- checkin possible outputs
 *
 */

#include <iostream>
#include "serverSocket.h"
#include "centralControl.h"
#include "user.h"

using namespace std;

// Functions declarations

/**
 *	Main call handler that checks which command was asked and choose the correct handler.
 *	@param control The pointer to the main CentralControl.
 *	@param input String sent by the caller.
 *	@return The output to send to the caller.
	 */
string callHandler(CentralControl* control, string& input);

/**
 *	Receives the input string and separates in command, caller id, caller password and the user input.
 *	@param input The string to be broken down.
 *	@param command The command requested by caller.
 *	@param id The caller id.
 *	@param password The caller password.
 *	@param userInput The rest of the input sent by the user
 *	@return The target id to be modified if it was sent by the user. Else 0.
 *	@throw "Missing id and password and not getActiveUsers".
 *	@throw "Missing password and not getActiveUsers".
 *	@throw "Wrong id input".
 */
unsigned long int getCommandIdPassInput(string& input, string& command, unsigned long int& id, string& password, string& userInput);

/**
 *	Checkin handler that tries to checkin the user in the CentralControl.
 *	@param control The pointer to the main CentralControl.
 *	@param output The output to send to the caller.
 *	@param id The caller id.
 *	@param password The caller password.
 */
void checkinHandler(CentralControl* control, string& output, unsigned long int id, string& password);

/**
 *	Handler that tries to get all the active users id,name,phone,email and save in output.
 *	@param control The pointer to the main CentralControl.
 *	@param output The output to send to the caller.
 */
void getActiveUsersHandler(CentralControl* control, string& output);

/**
 *	Checkout handler that tries to checkout the user in the CentralControl.
 *	@param control The pointer to the main CentralControl.
 *	@param output The output to send to the caller.
 *	@param id The caller id.
 *	@param password The caller password.
 */
void checkoutHandler(CentralControl* control, string& output, unsigned long int id, string& password);

/**
 *	Handler to open the door that tries to call openDoor in the CentralControl.
 *	@param control The pointer to the main CentralControl.
 *	@param output The output to send to the caller.
 *	@param id The caller id.
 *	@param password The caller password.
 */
void openDoorHandler(CentralControl* control, string& output, unsigned long int id, string& password);

/**
 *	Handler to create a user that tries to call createUser in the CentralControl.
 *	@param control The pointer to the main CentralControl.
 *	@param output The output to send to the caller.
 *	@param id The caller id.
 *	@param password The caller password.
 *	@param newUserInput The new user to be created in string format. See user.h.
 */
void createUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, string& newUserInput);

/**
 *	Handler to get a user that tries to call readUser in the CentralControl.
 *	@param control The pointer to the main CentralControl.
 *	@param output The output to send to the caller.
 *	@param id The caller id.
 *	@param password The caller password.
 *	@param targetId The user id to be read.
 */
void readUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, unsigned long int targetId);

/**
 *	Handler to edit a user that tries to call updateUser in the CentralControl.
 *	@param control The pointer to the main CentralControl.
 *	@param output The output to send to the caller.
 *	@param id The caller id.
 *	@param password The caller password.
 *	@param newUserInput The new user to be updated in string format. See user.h.
 */
void updateUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, string& newUserInput);

/**
 *	Handler to delete a user that tries to call deleteUser in the CentralControl.
 *	@param control The pointer to the main CentralControl.
 *	@param output The output to send to the caller.
 *	@param id The caller id.
 *	@param password The caller password.
 *	@param targetId The user id to be deleted.
 */
void deleteUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, unsigned long int targetId);

int main() {
	CentralControl* control = new CentralControl();

	cout << "Running....\n";

	try {
		// Create the socket
		ServerSocket server(8888);

	while (true) {
			ServerSocket newSocket;

			// Keeps waiting here until a new socket is accepted
			server.accept(newSocket);

			cout << "Connected!" << endl;

			try {
				string input, output;
				// Receive the input sent by the caller
				newSocket >> input;

				output = callHandler(control, input);

				cout << "Returned: " << output;
				// Return the handled output to the caller
				newSocket << output;
			} catch (SocketException& e) {
				cout << "Socket exception was caught: " << e.description() << endl;
			}
			cout << endl;
		}
	} catch (SocketException& e) {
		cout << "Exception was caught: " << e.description() << "\nExiting.\n";
	}

	delete control;
	return 0;
}

string callHandler(CentralControl* control, string& input) {
	string output, command, password, userInput;
	unsigned long int id, targetId;

	try {
		targetId = getCommandIdPassInput(input, command, id, password, userInput);
	} catch (const char* e) {
		output = e;
		output += "\n";
		return output;
	}

	if (command == "checkin") {
		cout << "Got checkin\n";
		checkinHandler(control, output, id, password);
		return output;
	}

	if (command == "getActiveUsers") {
		cout << "Got getActiveUsers\n";
		getActiveUsersHandler(control, output);
		return output;
	}

	if (command == "checkout") {
		cout << "Got checkout\n";
		checkoutHandler(control, output, id, password);
		return output;
	}

	if (command == "openDoor") {
		cout << "Got openDoor\n";
		openDoorHandler(control, output, id, password);
		return output;
	}

	if (command == "createUser") {
		cout << "Got createUser\n";
		createUserHandler(control, output, id, password, userInput);
		return output;
	}

	if (command == "readUser") {
		cout << "Got readUser\n";
		readUserHandler(control, output, id, password, targetId);
		return output;
	}

	if (command == "updateUser") {
		cout << "Got updateUser\n";
		updateUserHandler(control, output, id, password, userInput);
		return output;
	}

	if (command == "deleteUser") {
		cout << "Got deleteUser\n";
		deleteUserHandler(control, output, id, password, targetId);
		return output;
	}

	output = "Wrong command\n";
	return output;
}

unsigned long int getCommandIdPassInput(string& input, string& command, unsigned long int& id, string& password, string& userInput) {
	size_t initialPosition, finalPosition;
	unsigned long int targetId = 0;
	
	// Find command which must be first variable
	finalPosition = input.find(',', 0);
	command = input.substr(0, finalPosition);
	if (finalPosition == string::npos) {
		if (command == "getActiveUsers") {
			return 0;
		}
		if (command == "getActiveUsers\n") {
			command = command.substr(0, (command.length() - 1));
			return 0;
		}
		throw "Missing id and password and not getActiveUsers";
	}

	// Find id which must be following variable
	initialPosition = finalPosition + 1;
	finalPosition = input.find(',', initialPosition);
	if (finalPosition == string::npos) {
		throw "Missing password and not getActiveUsers";
	}
	try {
		id = stoul(input.substr(initialPosition, finalPosition - initialPosition));
	} catch (...) {
		throw "Wrong id input";
	}

	// Find password which must be following variable. Return if there is no userInput
	initialPosition = finalPosition + 1;
	finalPosition = input.find(',', initialPosition);
	if (finalPosition == string::npos) {
		size_t endlPosition = input.find('\n', initialPosition);
		// if there is a \n in the end of this input, save password without the \n
		if (endlPosition != finalPosition) {
			password = input.substr(initialPosition, endlPosition - initialPosition);
			return 0;
		}
		password = input.substr(initialPosition, finalPosition - initialPosition);
		return 0;
	}
	password = input.substr(initialPosition, finalPosition - initialPosition);

	// Find userInput which must be following variable. If the input is only an id, return the id
	initialPosition = finalPosition + 1;
	finalPosition = input.find('\n', initialPosition);
	userInput = input.substr(initialPosition, finalPosition - initialPosition);
	try {
		targetId = stoul(userInput);
	} catch (...) {
		userInput += "\n";
		return 0;
	}
	userInput += "\n";
	return targetId;
}

void checkinHandler(CentralControl* control, string& output, unsigned long int id, string& password) {
	try {
		control->checkin(id, password);
	} catch (const char* e) {
		// If the user is already checked in, there was a server failure and now it must be sync with phone.
		if (strcmp(e, "Id already exists") == 0) {
			output = "Checked-in with success,";
			if (control->canModifyDatabase(id)) {
				output += "admin\n";
			} else {
				output += "user\n";
			}
			cout << "User already is checked-in\n";
			return;
		}
		output = e;
		output += "\n";
		return;
	}
	output = "Checked-in with success,";
	if (control->canModifyDatabase(id)) {
		output += "admin\n";
	} else {
		output += "user\n";
	}
	return;
}

void getActiveUsersHandler(CentralControl* control, string& output) {
	try {
		output = control->getActiveUsers();
	} catch (const char* e) {
		output = e;
		output += "\n";
		return;
	}
	return;
}

void checkoutHandler(CentralControl* control, string& output, unsigned long int id, string& password) {
	try {
		control->checkout(id);
	} catch (const char* e) {
		// The user can only asks for this on the app if already checked in. So check in and try again.
		checkinHandler(control, output, id, password);
		if ((output == "Checked-in with success,admin\n") || (output == "Checked-in with success,user\n")) {
			try {
				control->checkout(id);
			} catch (const char* e) {
				output = e;
				output += "\n";
				return;
			}
			output = "Checked-out with success\n";
			return;
		}
		return;
	}
	output = "Checked-out with success\n";
	return;
}

void openDoorHandler(CentralControl* control, string& output, unsigned long int id, string& password) {
	try {
		control->openDoor(id);
	} catch (const char* e) {
		// The user can only asks for this on the app if already checked in. So check in and try again.
		checkinHandler(control, output, id, password);
		if ((output == "Checked-in with success,admin\n") || (output == "Checked-in with success,user\n")) {
			try {
				control->openDoor(id);
			} catch (const char* e) {
				output = e;
				output += "\n";
				return;
			}
			output = "Door opened\n";
			return;
		}
		return;
	}
	output = "Door opened\n";
	return;
}

void createUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, string& newUserInput) {
	try {
		control->createUser(id, newUserInput);
	} catch (const char* e) {
		// The user can only asks for this on the app if already checked in.
		// So if there is no permition, must be because of server failure. Check in and try again.
		if (strcmp(e, "No permission to create user") == 0) {
			checkinHandler(control, output, id, password);
			if ((output == "Checked-in with success,admin\n") || (output == "Checked-in with success,user\n")) {
				try {
					control->createUser(id, newUserInput);
				} catch (const char* e) {
					output = e;
					output += "\n";
					return;
				}
				output = "User created\n";
			}
			return;
		}
		output = e;
		output += "\n";
		return;		
	}
	output = "User created\n";
	return;
}

void readUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, unsigned long int targetId) {
	try {
		output = control->readUser(id, targetId);
	} catch (const char* e) {
		// The user can only asks for this on the app if already checked in.
		// So if there is no permition, must be because of server failure. Check in and try again.
		if (strcmp(e, "No permission to read user") == 0) {
			checkinHandler(control, output, id, password);
			if ((output == "Checked-in with success,admin\n") || (output == "Checked-in with success,user\n")) {
				try {
					output = control->readUser(id, targetId);
				} catch (const char* e) {
					output = e;
					output += "\n";
					return;
				}
				return;
			}
		}
		output = e;
		output += "\n";
		return;	
	}
	return;
}

void updateUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, string& newUserInput) {
	try {
		control->updateUser(id, newUserInput);
	} catch (const char* e) {
		// The user can only asks for this on the app if already checked in.
		// So if there is no permition, must be because of server failure. Check in and try again.
		if (strcmp(e, "No permission to update user") == 0) {
			checkinHandler(control, output, id, password);
			if ((output == "Checked-in with success,admin\n") || (output == "Checked-in with success,user\n")) {
				try {
					control->updateUser(id, newUserInput);
				} catch (const char* e) {
					output = e;
					output += "\n";
					return;
				}
				output = "User updated\n";
			}
			return;
		}
		output = e;
		output += "\n";
		return;		
	}
	output = "User updated\n";
	return;
}

void deleteUserHandler(CentralControl* control, string& output, unsigned long int id, string& password, unsigned long int targetId) {
	try {
		control->deleteUser(id, targetId);
	} catch (const char* e) {
		// The user can only asks for this on the app if already checked in.
		// So if there is no permition, must be because of server failure. Check in and try again.
		if (strcmp(e, "No permission to delete user") == 0) {
			checkinHandler(control, output, id, password);
			if ((output == "Checked-in with success,admin\n") || (output == "Checked-in with success,user\n")) {
				try {
					control->deleteUser(id, targetId);
				} catch (const char* e) {
					output = e;
					output += "\n";
					return;
				}
				output = "User deleted\n";
			}
			return;
		}
		output = e;
		output += "\n";
		return;		
	}
	output = "User deleted\n";
	return;
}

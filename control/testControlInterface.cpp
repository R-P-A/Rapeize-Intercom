#include <iostream>
#include "controlInterface.h"

using namespace std;

int main() {
	ControlInterface* temp = new ControlInterface();
	string dataBaseName = "userDataBase";
	temp->findUser(1, dataBaseName);
	delete temp;
	return 0;
}
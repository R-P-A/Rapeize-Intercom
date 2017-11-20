#ifndef SOCKETEXCEPTION
#define SOCKETEXCEPTION

#include <string>

using namespace std;

class SocketException {
	private:
		string message;

	public:
		SocketException(string s) : message (s) {}
		string description() {
			return message;
		}
};

#endif	// SOCKETEXCEPTION
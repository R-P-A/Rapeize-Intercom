/** 
 *	@author  Rafael Pintar Alevato
 *	@date    20/11/2017
 *	@version 1.0 
 *	
 *	@brief Class that manages socket exceptions.
 *
 */

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
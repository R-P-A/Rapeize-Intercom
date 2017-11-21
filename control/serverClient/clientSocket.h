#ifndef CLIENTSOCKET
#define CLIENTSOCKET

#include "socket.h"
#include "socketException.h"

using namespace std;

class ClientSocket : private Socket {
	public:
 		ClientSocket(string host, int port);

 		const ClientSocket& operator << (const string&) const;
 		const ClientSocket& operator >> (string&) const;
};

#endif	// CLIENTSOCKET
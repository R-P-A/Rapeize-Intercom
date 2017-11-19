#ifndef SERVERSOCKET
#define SERVERSOCKET

#include "socket.h"
#include "socketException.h"

using namespace std;

class ServerSocket : private Socket {
	public:
		ServerSocket(int port);
		ServerSocket(){};
		virtual ~ServerSocket();

		const ServerSocket& operator << (const string&) const;
		const ServerSocket& operator >> (string&) const;

		void accept(ServerSocket&);
};

#endif	// SERVERSOCKET

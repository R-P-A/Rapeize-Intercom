/** 
 *	@author  Rafael Pintar Alevato
 *	@date    20/11/2017
 *	@version 1.0 
 *	
 *	@brief Class that manages the server sockets.
 *
 *	@section DESCRIPTION
 *	
 *	To do.
 *
 */


#ifndef SERVERSOCKET
#define SERVERSOCKET

#include "socket.h"
#include "socketException.h"

using namespace std;

class ServerSocket : private Socket {
	public:
		/** Constructor that already sets the socket with given port */
		ServerSocket(int port);
		ServerSocket() {};
		virtual ~ServerSocket();

		/** Accept connection to the socket */
		void accept(ServerSocket&);
		/** Send a string to the connected socket */
		const ServerSocket& operator << (const string&) const;
		/** Receive a string from the connected socket */
		const ServerSocket& operator >> (string&) const;
};

#endif	// SERVERSOCKET

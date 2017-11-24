/** 
 *	@author  Rafael Pintar Alevato
 *	@date    20/11/2017
 *	@version 1.0 
 *	
 *	@brief Class that manages the client sockets.
 *
 *	@section DESCRIPTION
 *	
 *	To do.
 *
 */

#ifndef CLIENTSOCKET
#define CLIENTSOCKET

#include "socket.h"
#include "socketException.h"

using namespace std;

class ClientSocket : private Socket {
	public:
		/** Create a new socket to connect with given IP and Port */
 		ClientSocket(string host, int port);

 		/** Send a string to the connected socket */
 		const ClientSocket& operator << (const string&) const;
		/** Receive a string from the connected socket */
 		const ClientSocket& operator >> (string&) const;
};

#endif	// CLIENTSOCKET
#include "clientSocket.h"

ClientSocket::ClientSocket(string host, int port) {
	if (!Socket::create()) {
    	throw SocketException("Could not create client socket.");
    }

  	if (!Socket::connect(host, port)) {
     	throw SocketException("Could not bind to port.");
    }
}


const ClientSocket& ClientSocket::operator << (const string& s) const {
	if (!Socket::send(s)) {
    	throw SocketException ("Could not write to socket.");
    }
  	return *this;
}


const ClientSocket& ClientSocket::operator >> (string& s) const {
	if (!Socket::recv(s)) {
		throw SocketException("Could not read from socket.");
    }
  	return *this;
}
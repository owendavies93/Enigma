#ifndef NETWORKED_H
#define NETWORKED_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <arpa/inet.h>

class Networked {
	private:
		static const int bufferLength = 256;
	protected:
		char _buffer[bufferLength];
		struct sockaddr_in _serverAddress;
		int _portno;
		int _sockfd;
		socklen_t _addressLength;
		char _addr[INET_ADDRSTRLEN];
		void error(const char *msg);
		void readSocket(int socket);
		void writeSocket(int socket);
	public:
		virtual void init() = 0;
};

#endif
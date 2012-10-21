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

#include "enigma.h"

class Networked {
	protected:
		static const int bufferLength = 2048;
		char _buffer[bufferLength];
		struct sockaddr_in _serverAddress;
		int _portno;
		int _sockfd;
		socklen_t _addressLength;
		char _addr[INET_ADDRSTRLEN];
		bool _verbose;
		void error(const char *msg);
		void verbose(const char *msg);
	public:
		virtual void init(Enigma &machine) = 0;
		void setVerboseFlag(bool setting);
};

#endif
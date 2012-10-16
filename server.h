#ifndef SERVER_H
#define SERVER_H

#include "networked.h"

class Server : public Networked {
private:
	struct sockaddr_in _clientAddress;
	int _newsockfd;
	Server();
public:
	virtual void init();
	Server(int portno);
};

#endif
#ifndef SERVER_H
#define SERVER_H

#include "networked.h"

class Server : public Networked {
private:
	struct sockaddr_in _clientAddress;
	int _newsockfd;
public:
	Server(int portno);
	virtual void init(Enigma &machine);
};

#endif
#ifndef CLIENT_H
#define CLIENT_H

#include "networked.h"

class Client : public Networked {
private:
	struct hostent *_server;
public:
	Client(char * hostname, int portno);
	virtual void init();
};

#endif
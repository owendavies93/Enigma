#include "server.h"

using namespace std;

Server::Server(int portno) {
	_portno = portno;
}

void Server::init(Enigma &machine) {
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0) {
		error("could not open socket.");
	}

	bzero((char*) &_serverAddress, sizeof(_serverAddress));
	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_addr.s_addr = INADDR_ANY;
	_serverAddress.sin_port = htons(_portno);
	if (bind(_sockfd, (struct sockaddr *) &_serverAddress, 
					  sizeof(_serverAddress)) < 0) {
		error("could not bind socket.");
	}
	listen(_sockfd, 5);

	_addressLength = sizeof(_clientAddress);
	_newsockfd = accept(_sockfd, (struct sockaddr *) &_clientAddress, 
								 &_addressLength);

	if (_newsockfd < 0) {
		error("could not open socket.");
	} else {
		inet_ntop(AF_INET, &(_clientAddress.sin_addr), _addr, INET_ADDRSTRLEN);
		cout << "Connected to " << _addr << endl;
	}

	while(1) {
		bzero(_buffer,256);
        int n = read(_newsockfd, _buffer, 255);
        strcpy(_buffer, machine.encrypt(_buffer, true));
        cout << _buffer << endl;
        if (n < 0) { 
            error("could not read from socket.");
        } else if (n == 0) {
            error("connection closed.");
        }
        cout << _addr << "> " << _buffer << endl;

        bzero(_buffer,256);
        cout << "Write message:" << endl << "> ";
        fgets(_buffer, 255, stdin);
        
        char* encrypt = machine.encrypt(_buffer, true);
    	if (strcmp(encrypt, "") == 0) {
    		continue;
    	}
    	strcpy(_buffer, encrypt);

        cout << _buffer << endl;
        n = write(_newsockfd, _buffer, strlen(_buffer));
        if (n < 0) {
            error("could not write to socket.");
        }
	}
	close(_newsockfd);
	close(_sockfd);
}
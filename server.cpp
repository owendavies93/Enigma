#include "server.h"

using namespace std;

Server::Server(int portno) {
	_portno = portno;
}

void Server::init() {
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
		readSocket(_newsockfd);
		writeSocket(_newsockfd);
	}
	close(_newsockfd);
	close(_sockfd);
}
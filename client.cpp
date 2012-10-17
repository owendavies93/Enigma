#include "client.h"

using namespace std;

Client::Client(char* hostname, int portno) {
	_portno = portno;
	_server = gethostbyname(hostname);
	if (_server == NULL) {
		error("no host could be found with that name.");
	}
}

void Client::init() {
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0) {
		error("could not open socket.");
	}

	bzero((char *) &_serverAddress, sizeof(_serverAddress));
	_serverAddress.sin_family = AF_INET;
	bcopy((char *) _server->h_addr, (char *) &_serverAddress.sin_addr.s_addr, 
									_server->h_length);

	_serverAddress.sin_port = htons(_portno);
	_addressLength = sizeof(_serverAddress);

	if (connect(_sockfd, (struct sockaddr*) &_serverAddress, _addressLength) 
		< 0) {
		error ("could not connect to host.");
	} else {
		inet_ntop(AF_INET, &(_serverAddress.sin_addr), _addr, INET_ADDRSTRLEN);
		cout << "Connected to " << _addr << endl;
	}

	while(1) {
		// writeSocket(_sockfd);
		// readSocket(_sockfd);
		bzero(_buffer, 256);
        cout << "Write message:" << endl << "> ";
        fgets(_buffer, 255, stdin);
        int n = write(_sockfd, _buffer, strlen(_buffer));
        if (n < 0) {
            error("Error - could not write to socket.");
        }

        bzero(_buffer, 256);
        n = read(_sockfd, _buffer, 255);
        if (n < 0) {
            error("Error - could not read from socket.");
        } else if (n == 0) {
            error("Error - connection closed.");
        }
        cout << _addr << "> " << _buffer << endl;
	}
	close(_sockfd);
}
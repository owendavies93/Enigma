#include "server.h"

using namespace std;

Server::Server(int portno) {
	_portno = portno;
}

void Server::init(Enigma &machine) {
	verbose("Setting up socket...");
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0) {
		error("could not open socket.");
	}

	bzero((char*) &_serverAddress, sizeof(_serverAddress));
	verbose("Configuring server address settings...");
	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_addr.s_addr = INADDR_ANY;
	_serverAddress.sin_port = htons(_portno);
	if (bind(_sockfd, (struct sockaddr *) &_serverAddress, 
					  sizeof(_serverAddress)) < 0) {
		error("could not bind socket.");
	}
	listen(_sockfd, 5);
	verbose("Waiting for connection...");

	_addressLength = sizeof(_clientAddress);
	_newsockfd = accept(_sockfd, (struct sockaddr *) &_clientAddress, 
								 &_addressLength);
	verbose("Accepting connection...");

	if (_newsockfd < 0) {
		error("could not open socket.");
	} else {
		inet_ntop(AF_INET, &(_clientAddress.sin_addr), _addr, INET_ADDRSTRLEN);
		cout << "Connected to " << _addr << endl;
	}

	while(1) {
		bzero(_buffer, bufferLength);
        int n = read(_newsockfd, _buffer, bufferLength - 1);
        verbose("Reading encrypted message:");
        verbose(_buffer);
        verbose("Unencrypting...");
        strcpy(_buffer, machine.encrypt(_buffer, true));
        if (n < 0) { 
            error("could not read from socket.");
        } else if (n == 0) {
            cout << "Connection closed." << endl;
        }
        cout << _addr << "> " << _buffer << endl;

        bzero(_buffer, bufferLength);
        cout << "Write message:" << endl << "> ";
        fgets(_buffer, bufferLength - 1, stdin);
		if (strstr(_buffer, ":q") != '\0') {
    		cout << "Qutting..." << endl;
    		break;
    	}
        char* encrypt = machine.encrypt(_buffer, true);

    	verbose("Encrypting message as:");
    	verbose(encrypt);
    	if (strcmp(encrypt, "") == 0) {
    		continue;
    	}
    	strcpy(_buffer, encrypt);

    	verbose("Sending message to client...");
        n = write(_newsockfd, _buffer, strlen(_buffer));
        if (n < 0) {
            error("could not write to socket.");
        } else {
        	verbose("Message sent.");
        }
	}
	close(_newsockfd);
	close(_sockfd);
}
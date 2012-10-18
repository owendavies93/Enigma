#include "client.h"

using namespace std;

Client::Client(char* hostname, int portno) {
	_portno = portno;
	_server = gethostbyname(hostname);
	if (_server == NULL) {
		error("no host could be found with that name.");
	}
}

void Client::init(Enigma &machine) {
	verbose("Setting up socket...");
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0) {
		error("could not open socket.");
	}

	verbose("Configuring server address settings...");
	bzero((char *) &_serverAddress, sizeof(_serverAddress));
	_serverAddress.sin_family = AF_INET;
	bcopy((char *) _server->h_addr, (char *) &_serverAddress.sin_addr.s_addr, 
									_server->h_length);

	_serverAddress.sin_port = htons(_portno);
	_addressLength = sizeof(_serverAddress);
	verbose("Attemping to connect...");

	if (connect(_sockfd, (struct sockaddr*) &_serverAddress, _addressLength) 
		< 0) {
		error ("could not connect to host.");
	} else {
		inet_ntop(AF_INET, &(_serverAddress.sin_addr), _addr, INET_ADDRSTRLEN);
		cout << "Connected to " << _addr << endl;
	}

	while(1) {
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
        int n = write(_sockfd, _buffer, strlen(_buffer));
        if (n < 0) {
            error("could not write to socket.");
        } else {
        	verbose("Message sent.");
        }

        bzero(_buffer, bufferLength);
        n = read(_sockfd, _buffer, bufferLength - 1);
        verbose("Reading encrypted message:");
        verbose(_buffer);
        verbose("Unencrypting...");
        strcpy(_buffer, machine.encrypt(_buffer, true));

        if (n < 0) {
            error("could not read from socket.");
        } else if (n == 0) {
            error("connection closed.");
        }
        cout << _addr << "> " << _buffer << endl;
	}
	close(_sockfd);
}
#include "networked.h"

using namespace std;

//This saves a lot of characters!
void Networked::error(const char *msg) {
	cerr << "Error - " << msg << endl;
	exit(1);
}

void Networked::readSocket(int socket) {
	bzero(_buffer, bufferLength);
    int n = read(socket, _buffer, bufferLength - 1);
    if (n < 0) {
        error("could not read from socket.");
    } else if (n == 0) {
        error("connection closed.");
    }
    cout << _addr << "> " << _buffer << endl;
}

void Networked::writeSocket(int socket) {
	bzero(_buffer, bufferLength);
    cout << "Write message:" << endl << "> ";
    fgets(_buffer, bufferLength - 1, stdin);
    int n = write(socket, _buffer, bufferLength);
    if (n < 0) {
        error("Error - could not write to socket.");
    }
}
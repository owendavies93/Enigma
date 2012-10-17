#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <algorithm>

#include "enigma.h"
#include "server.h"
#include "client.h"

using namespace std;

/*
    Check that CL arguments are valid (correct extensions, valid files), then
    provide cin for input, checking that all input is valid. Use the command :q 
    to end the program cleanly.
*/

bool findOption(char** start, char** end, const string &option) {
    return find(start, end, option);
}

char *getNextOption(char** start, char** end, const string &option) {
    char** iter = find(start, end, option);
    if (++iter != end) {
        return *iter;
    } else {
        return 0;
    };
}

int main(int argc, char **argv) {

    if (argc < 2) {
        cerr << "Error - Not enough arguments given. " <<
                 "You need at least a plugboard!" << endl;
        _exit(1);
    }

    int portno;
    char *host;
    bool server;

    if (findOption(argv, argv + argc, "-n")) {
        char *option = getNextOption(argv, argv + argc, "-n");
        if (strcmp(option, "server") == 0) {
            portno = atoi(getNextOption(argv, argv + argc, "server"));
            argc -= 3;
            server = true;
        } else if (strcmp(option, "client") == 0) {
            host = getNextOption(argv, argv + argc, "client");
            portno = atoi(getNextOption(argv, argv + argc, host));
            argc -= 4;
            server = false;
        }
    } 

    else if (!strstr(argv[argc - 1], ".pb")) {
        cerr << "Error - You need to specify a .pb file for your plugboard " <<
                "configuration." << endl;
        _exit(1);
    }

	// Parse .pb file to give to plugboard (via Enigma)
    int plugs[26];
    int size = 0;

    try {
        ifstream plugboardStream(argv[argc - 1], ifstream::in);

	    while (plugboardStream >> plugs[size]) {
	   	   ++size;
	    }
    } catch (ifstream::failure fail) {
        cerr << "Error - " << argv[argc - 1]  << " could not be read." << endl
             << strerror(errno) << endl;
        _exit(1);
    }

	// Create machine, with plugboard
    Enigma machine(plugs, size);

    // Create rotors if necessary
    for (int i = 1; i < argc - 1; i++) {
        try {
            ifstream rotorStream(argv[i], ifstream::in);
            rotorStream.exceptions(ifstream::failbit|ifstream::badbit);

            ifstream& streamRef = rotorStream;
            machine.addRotor(streamRef, i);
        } catch (ifstream::failure fail) {
            cerr << "Error - " << argv[i]  << " could not be read." << endl
                 << strerror(errno) << endl;
            _exit(1);
        }
    }

    if (findOption(argv, argv + (argc + 1), "-n")) {
        if (server) {
            Server server(portno);
            server.init(machine);
        } else {
            Client client(host, portno);
            client.init(machine);
        }
    } else {
        string inputString;
        while (getline(cin, inputString)) {
            if (inputString.find(":q") != string::npos) {
                close(0);
                cout << "Qutting..." << endl;
            } else {
                vector<char> cpy(inputString.size() + 1);
                copy(inputString.begin(), inputString.end(), cpy.begin());
                machine.encrypt(&cpy[0], false);
            }
        }
    }
    return 0;
}

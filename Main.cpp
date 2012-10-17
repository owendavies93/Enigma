#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "enigma.h"

using namespace std;

/*
    Check that CL arguments are valid (correct extensions, valid files), then
    provide cin for input, checking that all input is valid. Use the command :q 
    to end the program cleanly.
*/    
int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Error - Not enough arguments given. " <<
                 "You need at least a plugboard!" << endl;
        _exit(1);
    } else if (!strstr(argv[argc - 1], ".pb")) {
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

    string inputString;
    while (getline(cin, inputString)) {
        if (inputString.find(":q") != string::npos) {
            close(0);
            cout << "Qutting..." << endl;
        } else {
            machine.encrypt(inputString);
        }
    }

    return 0;
}

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "enigma.h"

using namespace std;

int main(int argc, char **argv) {
	// Parse .pb file to give to plugboard (via Enigma)
    int plugs[26];
    int size = 0;

    try {
        ifstream plugboardStream(argv[argc - 1], ifstream::in);
        //plugboardStream.exceptions(ifstream::failbit);

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

    cout << "Enter string to encode: ";
    string inputString;
    cin >> inputString;
    machine.encrypt(inputString);
}

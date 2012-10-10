#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "enigma.h"

using namespace std;

int main(int argc, char **argv) {
	//Parse .pb file to give to plugboard (via Enigma)
    int plugs[26];
    int size = 0;
    ifstream plugboardStream(argv[argc], ifstream::in);

	while (plugboardStream >> plugs[size]) {
		++size;
	}

	//Create machine, with plugboard
    Enigma machine(plugs, size);
    vector<ifstream*> streams;

    //Create rotors if necessary
    for (int i = 1; i < argc - 1; i++) {
        ifstream rotorStream(argv[i], ifstream::in);
        streams.push_back(&rotorStream);

        ifstream& streamRef = rotorStream;
        machine.addRotor(streamRef, i);
    }

    string inputString = "AAAAAAAAAAAAAAAAAAAAAAAAAA";

    machine.encrypt(inputString);
}

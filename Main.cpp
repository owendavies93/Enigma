#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "enigma.h"

using namespace std;

int main(int argc, char **argv) {
    cout << "Engima machine started." << endl;

    Enigma machine;
    vector<ifstream*> streams;

    for (int i = 1; i < argc; i++) {
        ifstream rotorStream(argv[i], ifstream::in);
        streams.push_back(&rotorStream);

        ifstream& streamRef = rotorStream;
        machine.addRotor(streamRef);
    }

    cout << "Rotors assembled." << endl;

    ifstream plugboardStream(argv[argc], ifstream::in);
    ifstream& plugboardStreamRef = plugboardStream;

    machine.createPlugboard(plugboardStreamRef);

    cout << "Plugboard assembled." << endl;
}

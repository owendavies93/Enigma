#ifndef ENIGMA_H
#define ENIGMA_H

#include "rotor.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Enigma {
    private:
        vector<Rotor> this_rotors;
		
    public:
        void addRotor(ifstream& config);
};

#endif

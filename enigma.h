#ifndef ENIGMA_H
#define ENIGMA_H

#include <fstream>
#include <iostream>
#include <vector>

#include "rotor.h"

using namespace std;

class Enigma {
private:
    vector<Rotor> this_rotors;
	
public:
    void addRotor(ifstream& config);
    void createPlugboard(ifstream& config);
};

#endif

#include "enigma.h"
#include "rotor.h"
#include <string>
#include <iostream>
#include <fstream>

const int alphabetLength = 26;

void Enigma::addRotor(ifstream& config) {
	int indicies[alphabetLength];
	
	for (int i = 0; i < alphabetLength; i++) {
		config >> indicies[i];
	}
	
    Rotor rot(indicies);
    this_rotors.push_back(rot);
}

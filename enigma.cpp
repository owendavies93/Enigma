#include <string>
#include <iostream>
#include <fstream>

#include "enigma.h"
#include "plugboard.h"
#include "rotor.h"

const int alphabetLength = 26;

void Enigma::addRotor(ifstream& config) {
	int indicies[alphabetLength]; //Array index represents original value
	
	for (int i = 0; i < alphabetLength; i++) {
		config >> indicies[i];
	}
	
    Rotor rot(indicies);
    this_rotors.push_back(rot);
}

void Enigma::createPlugboard(ifstream& config) {
	int plugs[alphabetLength];
	int size = 0;
	while (config >> plugs[size]) {
		++size;
	}


	Plugboard pb(plugs, size);
}

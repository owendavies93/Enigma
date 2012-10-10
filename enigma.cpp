#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "enigma.h"
#include "plugboard.h"
#include "rotor.h"

const int alphabetLength = 26;

Enigma::Enigma(int* plugboardConfig, int size) : _pb(plugboardConfig, size), _rf() {
	cout << "Reflector assembled." << endl;
}

void Enigma::addRotor(ifstream& config, int number) {
	int indicies[alphabetLength]; //Array index represents original value
	
	for (int i = 0; i < alphabetLength; i++) {
		config >> indicies[i];
	}
	
    Rotor rot(indicies, number);
    _rotors.push_back(rot);

    cout << "Rotor assembled." << endl;
}

void Enigma::printRotors() {
	vector<Rotor>::iterator it;
	
	cout << "_rotors contains:" << endl;
  	for (it = _rotors.begin(); it < _rotors.end(); it++) {
    	cout << it->getName() << endl;
  	}
}

void Enigma::printPlugboard() {

}

void Enigma::encrypt(string input) {
	for(unsigned i = 0; i < input.length(); i++) {
    	cout << encryptChar(input[i]);
	}
	cout << endl;
}

char Enigma::encryptChar(char input) {
	//send char throguh plugboard
	input = _pb.map(input);

	//reflect char
	input = _rf.map(input);

	//send char back thorugh plugboard
	input = _pb.map(input);
	
	return input;
}
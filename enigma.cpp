#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <string.h>

#include "enigma.h"
#include "plugboard.h"
#include "rotor.h"

const int alphabetLength = 26;
const int asciiStart= 65;

Enigma::Enigma(int* plugboardConfig, int size) : _pb(plugboardConfig, size), 
												 _rf() {}

void Enigma::addRotor(ifstream& config, int number) {
	map<int, int> inMap, outMap;
	
	for (int i = 0; i < alphabetLength; i++) {
		int val;
		config >> val;
		int target = (val - i + alphabetLength) % alphabetLength;
		inMap.insert(pair <int, int>(i, target));

		// Derive offset for reverse from original offset
		outMap.insert(pair <int, int>((target + i) % alphabetLength, 
									  (alphabetLength - target) % alphabetLength
									  )); 
	}

	Rotor rot(inMap, outMap, number);
	_rotors.push_back(rot);
}

void Enigma::printRotors() {
	vector<Rotor>::iterator it;
	
	cout << "_rotors contains:" << endl;
	for (it = _rotors.begin(); it < _rotors.end(); it++) {
		cout << it->getName() << endl;
		it->printRotor();
	}
}

void Enigma::printPlugboard() {
	_pb.printMaps();
}

char* Enigma::encrypt(char* conv, bool networking) {
	for (unsigned i = 0; i < strlen(conv); i++) {
        char curr = conv[i];
        if (!((isupper(curr) && isalpha(curr)) || isspace(curr))) {
            cerr << "Error - input string must be alphabetic and " << 
                    "upper case characters only (whitespace is also " << 
                    "allowed)." << endl;
			return NULL;
        }
        conv[i] = encryptChar(curr);
	}

	if (!networking) {
		cout << conv << endl;
	}
	
	return conv;
}

char Enigma::encryptChar(char input) {
	if (!isspace(input)) {
		int conv = (((int) input) - asciiStart) % alphabetLength;

		// Send character throguh plugboard
		conv = _pb.map(conv);

		// Send forward through rotors
		vector<Rotor>::iterator it;
		for (it = _rotors.begin(); it < _rotors.end(); ++it) {
			conv = it->map(conv);
		}

		// Reflect character
		conv = _rf.map(conv);

		// Send back through rotors
		vector<Rotor>::reverse_iterator rit;
		for (rit = _rotors.rbegin(); rit != _rotors.rend(); ++rit) {
			conv = rit->map(conv);
		}
		if ((int) _rotors.size() > 0) {
			rotateRotors(0);
		}

		// Send back thorugh plugboard
		conv = _pb.map(conv);

		return (char) (conv + asciiStart);
	} else {
		return ' ';		
	}
}

// Rotates the current rotor and then checks the next rotor recursively
void Enigma::rotateRotors(int num) {
	_rotors[num].rotate();
	if ((_rotors[num].getRotateModCount() == 0) && 
		(num + 1 != (int) _rotors.size())) {
		rotateRotors(num + 1);
	}
}

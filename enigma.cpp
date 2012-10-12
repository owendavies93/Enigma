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
	map<int, int> inMap, outMap;
	
	for (int i = 0; i < alphabetLength; i++) {
		int val;
		config >> val;
		inMap.insert(pair <int, int>(i, (val - i + 26) % 26));

		outMap.insert(pair <int, int>(
			(((val - i + 26) % 26) + i) % 26, 
			(26 - ((val - i + 26) % 26)) % 26
			)); //derives offset for reverse from original offset
	}

    Rotor rot(inMap, outMap, number);
    _rotors.push_back(rot);

    cout << "Rotor assembled." << endl;
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

void Enigma::encrypt(string conv) {
	for (unsigned i = 0; i < conv.length(); i++) {
       cout << encryptChar(conv[i]);
	}
	cout << endl;
}

char Enigma::encryptChar(char input) {
	int conv = (((int) input) - 65) % 26;

	//send char throguh plugboard
	conv = _pb.map(conv);

    //send through rotors
	vector<Rotor>::iterator it;
  	for (it = _rotors.begin(); it < _rotors.end(); ++it) {
    	conv = it->map(conv);
  	}

	//reflect char
	conv = _rf.map(conv);

	//send back through rotors
	vector<Rotor>::reverse_iterator rit;
  	for (rit = _rotors.rbegin(); rit != _rotors.rend(); ++rit) {
    	conv = rit->map(conv);
    }
    rotateRotors(0);

	//send char back thorugh plugboard
	conv = _pb.map(conv);

	return (char) (conv + 65);
}

void Enigma::rotateRotors(int num) {
    _rotors[num].rotate();
    if ((_rotors[num].getRotateModCount() == 0) && (num + 1 != _rotors.size())) {
        rotateRotors(num + 1);
    }
}


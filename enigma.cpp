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
		inMap.insert(pair <int, int>(i, val));
		outMap.insert(pair <int, int>(val, i));
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
  	}
}

void Enigma::printPlugboard() {
	_pb.printMaps();
}

void Enigma::encrypt(string input) {
	for (unsigned i = 0; i < input.length(); i++) {
    	cout << encryptChar(input[i]);
	}
	cout << endl;
}

char Enigma::encryptChar(char input) {
	//send char throguh plugboard
	input = _pb.map(input);

	//cout << "after plugboard: " << input << endl;




	vector<Rotor>::iterator it;
	
  	for (it = _rotors.begin(); it < _rotors.end(); it++) {
    	input = it->map(input);
  	}

	//cout << "after rotor: " << input << endl;




	//reflect char
	input = _rf.map(input);

	//cout << "after reflect: " << input << endl;




  	for (it = _rotors.begin(); it < _rotors.end(); it++) {
    	input = it->map(input);
  	}

	//cout << "after rotor: " << input << endl;




	//send char back thorugh plugboard
	input = _pb.map(input);

	//cout << "after plugboard: " << input << endl;

	return input;
}
#ifndef ENIGMA_H
#define ENIGMA_H

#include <fstream>
#include <iostream>
#include <vector>

#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"

using namespace std;

class Enigma {
private:
    Enigma();
    vector<Rotor> _rotors;
    Plugboard _pb;
    Reflector _rf;
	
public:
	Enigma(int* plugboardConfig, int plugboardSize);
    void addRotor(ifstream& config, int number);
    void printRotors();
    void printPlugboard();
    void encrypt(string input);
    char encryptChar(char input);
    void rotateRotors(int);
};

#endif

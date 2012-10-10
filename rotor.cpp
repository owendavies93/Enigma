#include <sstream>
#include <string>
#include <iostream>

#include "rotor.h"

using namespace std;

Rotor::Rotor(int* config, int num) {
	_config = config;
	stringstream ss;
	ss << "Rotor " << num;
	_name = ss.str();
}

char Rotor::map(char orig) {
	return _config[orig];
}

string Rotor::getName() {
	return _name;
}
#include "rotor.h"

using namespace std;

Rotor::Rotor(int* config) {
	_config = config;
}

int Rotor::map(int orig) {
	return _config[orig];
}
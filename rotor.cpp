#include <sstream>
#include <string>
#include <iostream>

#include "rotor.h"

using namespace std;

Rotor::Rotor(std::map<int, int> inMap, std::map<int, int> outMap, int num) {
	_inConfig = inMap;
	_outConfig = outMap;
	status = 0;

	stringstream ss;
	ss << "Rotor " << num;
	_name = ss.str();
}

char Rotor::map(char orig) {
	int conv = (((int) orig) - 64) % 26;

	if (!status) {
		status = 1;
		return (char) ((_inConfig.find(conv)->second) + 64);
	} else {
		status = 0;
		return (char) ((_outConfig.find(conv)->second) + 64);
	}
}

string Rotor::getName() {
	return _name;
}
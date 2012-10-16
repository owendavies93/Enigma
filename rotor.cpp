#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

#include "rotor.h"

using namespace std;

const int alphabetLength = 26;

Rotor::Rotor(std::map<int, int> inMap, std::map<int, int> outMap, int num) {
	_inConfig = inMap;
	_outConfig = outMap;
    _status = IN;

	stringstream ss;
	ss << "Rotor " << num;
	_name = ss.str();
    _rotateCount = _rotateModCount = 0;
}

int Rotor::map(int orig) {
	if (_status == IN) {
        orig += 
            _inConfig.find((orig + _rotateModCount) % alphabetLength)->second;
		_status = OUT;
		return orig % alphabetLength;
	} else {
        orig += 
            _outConfig.find((orig + _rotateModCount) % alphabetLength)->second;
		_status = IN;
		return orig % alphabetLength;
	}
}

string Rotor::getName() {
	return _name;
}

void Rotor::rotate() {
    _rotateCount++;
    _rotateModCount = _rotateCount % alphabetLength;
}

int Rotor::getRotateCount() {
    return _rotateCount;
}

int Rotor::getRotateModCount() {
    return _rotateModCount;
}

void Rotor::printRotor() {
    std::map<int, int>::iterator it;

    for (it = _inConfig.begin(); it != _inConfig.end(); ++it) {
        cout << it->first << " => " << it->second << endl;
    }

    cout << endl;

    for (it = _outConfig.begin(); it != _outConfig.end(); ++it) {
        cout << it->first << " => " << it->second << endl;
    }
}

std::map<int, int>& Rotor::getMap() {
    std::map<int, int>& ref = _inConfig;
    return ref;
}

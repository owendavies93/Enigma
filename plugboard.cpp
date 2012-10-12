#include <iostream>
#include <map>

#include "plugboard.h"

using namespace std;

Plugboard::Plugboard(int* config, int& size) {
	_config = config;
	_size = size;
	fillMaps();
}

int Plugboard::map(int orig) {
	if (_in.find(orig) == _in.end()) {
		return orig;
	} else {
		return _in.find(orig)->second;
	}
}

void Plugboard::fillMaps() {
	for (int i = 0; i < _size / 2; i+=2) {
		_in.insert(pair <int, int>(_config[i], _config[i + 1]));
		_in.insert(pair <int, int>(_config[i + 1], _config[i]));
	}

	cout << "Plugboard assembled" << endl;
}

void Plugboard::printMaps() {
	std::map<int, int>::iterator it;

	cout << "_in contains:\n";
  	for (it = _in.begin(); it != _in.end(); it++) {
    	cout << it->first << " => " << it->second << endl;
    }
}
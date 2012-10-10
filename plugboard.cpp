#include <iostream>
#include <map>

#include "plugboard.h"

using namespace std;

Plugboard::Plugboard(int* config, int& size) {
	_config = config;
	_size = size;
	fillMaps();
}

char Plugboard::map(char orig) {
	int conv = ((int) orig) - 64;

	if (_in.find(conv) == _in.end()) {
		return orig;
	} else {
		return (char) (_in.find(conv)->second + 64);
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
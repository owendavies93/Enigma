#include <iostream>
#include <map>

#include "plugboard.h"

using namespace std;

Plugboard::Plugboard(int* config, int size) {
	_config = config;
	_size = size;
	fillMaps();
}

int Plugboard::map(int orig) {
	return 0;
}

void Plugboard::fillMaps() {
	for (int i = 0; i < _size / 2; i+=2) {
		cout << i;
		_in.insert(pair <int, int>(_config[i], _config[i + 1]));
		_out.insert(pair <int, int>(_config[i + 1], _config[i]));
	}

}

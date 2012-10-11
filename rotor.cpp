#include <sstream>
#include <string>
#include <iostream>
#include <vector>

#include "rotor.h"

using namespace std;

Rotor::Rotor(std::map<int, int> inMap, std::map<int, int> outMap, int num) {
	_inConfig = inMap;
	_outConfig = outMap;
	status = 0; //DO THIS WITH AN ENUM

	stringstream ss;
	ss << "Rotor " << num;
	_name = ss.str();
}

char Rotor::map(char orig) {
	int conv = (((int) orig) - 65) % 26;

	if (!status) {
		status = 1;
		return (char) ((_inConfig.find(conv)->second) + 65);
	} else {
		status = 0;
		return (char) ((_outConfig.find(conv)->second) + 65);
	}


}

string Rotor::getName() {
	return _name;
}

void Rotor::rotate() {
    rotateForward();
    rotateBackward(_outConfig);
}

void Rotor::rotateForward() {
	vector<int> values(_inConfig.size());
	int j = 0;
	std::map<int, int>::iterator it;

	for (it = _inConfig.begin(); it != _inConfig.end(); it++) {
		values[j] = it->second;
        j++;
	}
    
	j = 1;

	for (it = _inConfig.begin(); it != _inConfig.end(); ++it) {
        _inConfig[it->first] = values[j % _inConfig.size()];
        j++;
	} 
}

void Rotor::rotateBackward(std::map<int, int>& m) {
    vector<int> values(m.size());
    
    int j = 0;
    std::map<int, int>::iterator it;

    for (it = m.begin(); it != m.end(); ++it) {
        values[j] = it->second;
        j++;
    }

    j = 25;

    for (it = m.begin(); it != m.end(); ++it) {
        m[it->first] = values[j % m.size()];
        j++;
    }
    
}

void Rotor::printRotor() {
    std::map<int, int>::iterator it;

    for (it = _inConfig.begin(); it != _inConfig.end(); ++it) {
        cout << it->first << " => " << it->second << endl;
    }

    cout << endl;

    /*for (it = _outConfig.begin(); it != _outConfig.end(); ++it) {
        cout << it->first << " => " << it->second << endl;
    }*/

}

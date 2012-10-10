#ifndef ROTOR_H
#define ROTOR_H

#include <string>

#include "component.h"

using namespace std;

class Rotor : public Component {
private:
	int* _config;
	string _name;
    Rotor();
		
public:
    Rotor(int* config, int num);
	virtual char map(char orig);
	string getName();
};

#endif

#ifndef ROTOR_H
#define ROTOR_H

#include "component.h"

using namespace std;

class Rotor : public Component {
private:
	int* _config;
    Rotor();
		
public:
    Rotor(int* config);
	virtual int map(int orig);
};

#endif

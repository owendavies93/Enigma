#ifndef ROTOR_H
#define ROTOR_H

#include <string>
#include "component.h"

using namespace std;

class Rotor : public Component {
    private:
        Rotor();
		
    public:
        Rotor(int* config);
		virtual int map(int orig);
};

#endif

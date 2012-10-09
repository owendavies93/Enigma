#ifndef ENIGMA_H
#define ENIGMA_H

#include "rotor.h"
#include <vector>

class Enigma {
    private:
        vector<Rotor> this_rotors;
    public:
        void addRotor(string encoding);
};

#endif

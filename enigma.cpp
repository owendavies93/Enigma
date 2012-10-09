#include "enigma.h"
#include <string>
#include <tr1/memory>

using namespace std;

void Enigma::addRotor(string encoding) {
    Rotor rot(encoding);
    this_rotors.push_back(rot);
}


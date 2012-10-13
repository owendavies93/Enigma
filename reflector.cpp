#include <iostream>

#include "reflector.h"

const int alphabetLength = 26;

int Reflector::map(int letter) {
	return (letter + 13) % alphabetLength;
}

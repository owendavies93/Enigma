#include <iostream>

#include "reflector.h"

int Reflector::map(int letter) {
	return (letter + 13) % 26;
}

#include <iostream>

#include "reflector.h"

char Reflector::map(char letter) {
	return (char) (((letter - 64) + 13) % 26) + 64;
}

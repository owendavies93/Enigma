#include <iostream>

#include "reflector.h"

char Reflector::map(char letter) {
	//DOESN'T WORK FOR M
	return (char) (((letter - 64) + 13) % 26) + 64;
}

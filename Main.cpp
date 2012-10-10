// skeleton C++ file, you will need to edit this and other files to implement your enigma machine
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "enigma.h"

using namespace std;

int main(int argc, char **argv) {
	Enigma machine;
	ifstream stream("plugboards/I.pb", ifstream::in);

	ifstream& streamRef = stream;
	machine.createPlugboard(streamRef);
}

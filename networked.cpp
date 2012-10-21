#include "networked.h"

using namespace std;

//These save a lot of characters!
void Networked::error(const char *msg) {
	cerr << "Error - " << msg << endl;
	exit(1);
}

void Networked::verbose(const char *msg) {
    if (_verbose) {
        cout << msg << endl;
    }
}

void Networked::setVerboseFlag(bool setting) {
    _verbose = setting;
}
#ifndef ROTOR_H
#define ROTOR_H

#include <map>
#include <string>

#include "component.h"

using namespace std;

class Rotor : public Component {
private:
	int status;
	std::map<int, int> _inConfig;
	std::map<int, int> _outConfig;
	string _name;
    Rotor();
    void rotateForward();
    void rotateBackward(std::map<int, int>& m);
		
public:
    Rotor(std::map<int, int> inMap, std::map<int, int> outMap, int num);
	virtual char map(char orig);
	string getName();
    void rotate();
    void printRotor();
};

#endif

#ifndef ROTOR_H
#define ROTOR_H

#include <map>
#include <string>

#include "component.h"

using namespace std;

enum status_t {IN, OUT};

class Rotor : public Component {
private:
    Rotor();
	status_t _status;
	std::map<int, int> _inConfig;
	std::map<int, int> _outConfig;
	string _name;
    int _rotateModCount;
    int _rotateCount;
    void rotateForward();
    void rotateBackward(std::map<int, int>& m);
		
public:
    Rotor(std::map<int, int> inMap, std::map<int, int> outMap, int num);
	virtual int map(int orig);
	string getName();
    void rotate();
    void printRotor();
    int getRotateCount();
    int getRotateModCount();
};

#endif

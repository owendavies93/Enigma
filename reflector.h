#ifndef REFLECTER_H
#define REFLECTER_H

#include "component.h"

class Reflector : public Component {

public:
	virtual int map(int orig) = 0;

};

#endif

#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "component.h"

class Reflector : public Component {

public:
	virtual int map(int orig);

};

#endif

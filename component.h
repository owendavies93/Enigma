#ifndef COMPONENT_H
#define COMPONENT_H

/*
	The Pluboard, Reflector and Rotor classes all inherit from this class
	defenition, and all implement the map method. 
*/
class Component {
	
public:
	virtual int map(int orig) = 0;
	
};

#endif

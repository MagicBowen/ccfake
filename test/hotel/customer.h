#ifndef H47C58302_663B_47C5_9408_C40CCEEFD01E
#define H47C58302_663B_47C5_9408_C40CCEEFD01E

#include "ccfake/actor/actor.h"

CCFAKE_NS_USING;

class Customer : public Actor {
public:
	Customer(std::string name)
	: name{name} {
	}

private:
	std::string name;
};

#endif

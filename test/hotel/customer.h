#ifndef H47C58302_663B_47C5_9408_C40CCEEFD01E
#define H47C58302_663B_47C5_9408_C40CCEEFD01E

#include "ccfake/actor/actor.h"

CCFAKE_NS_USING;

CCFAKE_ACTOR(Customer) {
public:
	Customer(std::string name)
	: name{name} {
	}

    template<typename CHECKER>
    void recv(const CHECKER& check) {
    	Actor::fetch(check);
    }

    template<typename CHECKER>
    void send(const CHECKER& check) {
    	Actor::submit(check);
    }

private:
	std::string name;
};

#endif

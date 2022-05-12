#ifndef H47C58302_663B_47C5_9408_C40CCEEFD01E
#define H47C58302_663B_47C5_9408_C40CCEEFD01E

#include "ccfake/actor/actor.h"
#include "ccfake/dtree/dtree.h"
#include "mail.h"

CCFAKE_NS_USING;

CCFAKE_ACTOR_TYPE(Customer) {
public:
	Customer(std::string name, DtreeNode &node)
	: name{name}, hotel{node} {
	}

    template<typename CHECKER>
    void recv(const CHECKER& check) {
    	Actor::fetch(check);
    }

    template<typename CHECKER>
    void send(const CHECKER& check) {
    	Actor::submit(check);
    }

    template<typename MSG = Mail>
    Mail::MsgPtr fetchMsg() {
    	CCFAKE_INFO("customer fetch msg");
    	auto mail = Mail::MsgPtr{new Mail};
    	mail->hotelName = "marriott";
    	return mail;
    }

    Status submitMsg(Mail::MsgPtr mail) {
    	CCFAKE_INFO("customer submit msg");
    	return Status::SUCCESS;
    }

private:
	std::string name;
    Dtree hotel;
};

#endif

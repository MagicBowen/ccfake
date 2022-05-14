#ifndef H47C58302_663B_47C5_9408_C40CCEEFD01E
#define H47C58302_663B_47C5_9408_C40CCEEFD01E

#include "ccfake/actor/actor.h"
#include "hotel/hotel.h"
#include "hotel/mail.h"

CCFAKE_NS_USING;

CCFAKE_ACTOR_TYPE(Customer) {
public:
	Customer(std::string name,  Hotel& hotel)
	: name{name}, hotel{hotel} {
	}

    template<typename CHECKER>
    void recvMail(const CHECKER& check) {
    	Actor::fetch(check);
    }

    template<typename CHECKER>
    void sendMail(const CHECKER& check) {
    	Actor::submit(check);
    }

private:
    Status fetchMsg(Mail& mail) {
    	auto mailBox = Dtree(hotel).get<MailBox>();
    	return mailBox->fetchMail(mail);
    }

    Status submitMsg(Mail& mail) {
    	auto mailBox = Dtree(hotel).get<MailBox>();
    	return mailBox->submitMail(mail);
    }

    friend struct Actor<Customer>;

private:
	std::string name;
    Hotel& hotel;
};

#endif

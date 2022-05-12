#ifndef HBF2E5504_6823_40F6_A6B7_D50701C666AE
#define HBF2E5504_6823_40F6_A6B7_D50701C666AE

#include "ccfake/base/traits.h"
#include "ccfake/base/status.h"
#include <string>

CCFAKE_NS_BEGIN

template<typename ACTOR>
struct Actor {
    template<typename CHECKER, typename MSG = CCFAKE_ARG_TYPE(CHECKER)>
    void fetch(const CHECKER& userCheck) {
        auto msg = static_cast<ACTOR*>(this)->template fetchMsg<MSG>();
        if (!msg) {
        	CCFAKE_FATAL("Actor fetched msg failed!");
        }
        if (!static_cast<ACTOR*>(this)->checkMsg(*msg)) {
        	CCFAKE_FATAL("Actor fetched msg failed!");
        }
        userCheck(*msg);
    }

    template<typename BUILDER, typename MSG = CCFAKE_ARG_TYPE(BUILDER)>
    void submit(const BUILDER& userBuild) {
        auto msg = static_cast<ACTOR*>(this)->template allocMsg<MSG>();
        if (!msg) {
        	CCFAKE_FATAL("Actor allocated msg failed!");
        }
        if (status_is_failed(static_cast<ACTOR*>(this)->buildMsg(*msg))) {
        	CCFAKE_FATAL("Actor builded msg failed!");
        }
        userBuild(*msg);
        if (status_is_failed(static_cast<ACTOR*>(this)->submitMsg(std::move(msg)))) {
        	CCFAKE_FATAL("Actor submitted msg failed!");
        }
    }

    template<typename MSG>
    typename MSG::MsgPtr fetchMsg();

    template<typename MSG_PTR>
    Status submitMsg(MSG_PTR);

    template<typename MSG>
    typename MSG::MsgPtr allocMsg() {
    	return typename MSG::MsgPtr{new MSG};
    }

    template<typename MSG>
    bool checkMsg(const MSG& msg) {
    	return true;
    }

    template<typename MSG>
    Status buildMsg(MSG& msg) {
    	return Status::SUCCESS;
    }
};

#define CCFAKE_ACTOR_TYPE(ACTOR)  struct ACTOR : ::CCFAKE_NS::Actor<ACTOR>

CCFAKE_NS_END

#endif

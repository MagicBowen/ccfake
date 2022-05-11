#ifndef HBF2E5504_6823_40F6_A6B7_D50701C666AE
#define HBF2E5504_6823_40F6_A6B7_D50701C666AE

#include "ccfake/dtree/dtree.h"
#include "ccfake/base/traits.h"

CCFAKE_NS_BEGIN

struct Actor {
    template<typename CHECKER, typename MSG = CCFAKE_ARG_TYPE(CHECKER)>
    void fetch(const CHECKER& check) {
        auto msg = MSG::fetch();
        if (!msg) {
        	CCFAKE_FATAL("Actor fetches msg failed!");
        }
        check(*msg);
    }

    template<typename BUILDER, typename MSG = CCFAKE_ARG_TYPE(BUILDER)>
    void submit(const BUILDER& build) {
        auto msg = typename MSG::MsgPtr{new MSG};
        build(*msg);
        if (status_is_failed(MSG::submit(std::move(msg)))) {
        	CCFAKE_FATAL("Actor submit msg failed!");
        }
    }
};

#define CCFAKE_ACTOR(ACTOR)  struct ACTOR : ::CCFAKE_NS::Actor

CCFAKE_NS_END

#endif

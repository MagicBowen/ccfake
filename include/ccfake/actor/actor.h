#ifndef HBF2E5504_6823_40F6_A6B7_D50701C666AE
#define HBF2E5504_6823_40F6_A6B7_D50701C666AE

#include "ccfake/dtree/dtree.h"
#include "ccfake/base/traits.h"

CCFAKE_NS_BEGIN

struct Actor {
    template<typename CHECKER>
    void expect(const CHECKER& check) {
        using MSG = CCFAKE_ARG_TYPE(CHECKER);
        MSG *msg = MSG::pop();
        if (!msg) {
        	CCFAKE_FATAL("Actor fetches msg failed!");
        }
        check(*msg);
    }

    template<typename BUILDER>
    void submit(const BUILDER& build) {
        using MSG = CCFAKE_ARG_TYPE(BUILDER);
        MSG msg;
        build(msg);
        if (status_is_failed(MSG::put(msg))) {
        	CCFAKE_FATAL("Actor submit msg failed!");
        }
    }
};

CCFAKE_NS_END

#endif

#ifndef HBF2E5504_6823_40F6_A6B7_D50701C666AE
#define HBF2E5504_6823_40F6_A6B7_D50701C666AE

#include "ccfake/base/traits.h"
#include "ccfake/base/status.h"
#include "ccfake/log/log.h"
#include <string>

CCFAKE_NS_BEGIN

template<typename ACTOR>
struct Actor {
    template<typename CHECKER, typename MSG = CCFAKE_ARG_TYPE(CHECKER)>
    void fetch(const CHECKER& userCheck) {
    	MSG msg;
        if (status_is_failed(static_cast<ACTOR*>(this)->fetchMsg(msg))) {
        	CCFAKE_FATAL("Actor fetched msg failed!");
        }
        if (status_is_failed(static_cast<ACTOR*>(this)->checkMsg(msg))) {
        	CCFAKE_FATAL("Actor fetched msg failed!");
        }
        userCheck(msg);
    }

    template<typename BUILDER, typename MSG = CCFAKE_ARG_TYPE(BUILDER)>
    void submit(const BUILDER& userBuild) {
    	MSG msg;
        if (status_is_failed(static_cast<ACTOR*>(this)->buildMsg(msg))) {
        	CCFAKE_FATAL("Actor builded msg failed!");
        }
        userBuild(msg);
        if (status_is_failed(static_cast<ACTOR*>(this)->submitMsg(msg))) {
        	CCFAKE_FATAL("Actor submitted msg failed!");
        }
    }

protected:
    template<typename MSG>
    Status fetchMsg(MSG&) {
    	return Status::SUCCESS;
    }

    template<typename MSG>
    Status submitMsg(MSG&) {
    	return Status::SUCCESS;
    }

    template<typename MSG>
    Status checkMsg(MSG&) {
    	return Status::SUCCESS;
    }

    template<typename MSG>
    Status buildMsg(MSG& msg) {
    	return Status::SUCCESS;
    }
};

#define CCFAKE_ACTOR_TYPE(ACTOR)  struct ACTOR : ::CCFAKE_NS::Actor<ACTOR>

CCFAKE_NS_END

#endif

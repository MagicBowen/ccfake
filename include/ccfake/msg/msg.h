#ifndef HAA60331C_EFAF_41A8_9A5A_A714D4F53C61
#define HAA60331C_EFAF_41A8_9A5A_A714D4F53C61

#include "ccfake/base/ns.h"
#include <memory>

CCFAKE_NS_BEGIN

template<typename MSG>
struct FakeMsg {
	using MsgPtr = std::unique_ptr<MSG>;
};

#define CCFAKE_MSG(MSG)  struct MSG : ::CCFAKE_NS::FakeMsg<MSG>

CCFAKE_NS_END

#endif

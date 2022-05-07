#ifndef CCFAKE_07052CD0C24546F698F8AEA1C466E8AA
#define CCFAKE_07052CD0C24546F698F8AEA1C466E8AA

#include "ccfake/base/ns.h"
#include <type_traits>

CCFAKE_NS_BEGIN

template<typename E>
constexpr auto enum_underlying_cast(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}

CCFAKE_NS_END

#endif

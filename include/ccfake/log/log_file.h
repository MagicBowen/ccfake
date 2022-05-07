#ifndef CCFAKE_0147580959C8449495787C720969B030
#define CCFAKE_0147580959C8449495787C720969B030

#include "ccfake/base/ns.h"
#include <string>

CCFAKE_NS_BEGIN

namespace detail {
    template<std::size_t Len>
    constexpr const char* baseNameImpl(const char(&str)[Len], std::size_t pos)
    {
        return pos==0 ? str : (str[pos] == '/' || str[pos] == '\\') ? str+pos+1 : baseNameImpl(str, --pos);
    }
}

template<std::size_t Len>
constexpr const char* log_file_base_name(const char(&str)[Len])
{
    return detail::baseNameImpl(str, Len-1);
}

CCFAKE_NS_END

#endif

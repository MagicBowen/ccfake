#ifndef H3D1CF06F_8F91_49EE_A5BB_381EF75062C8
#define H3D1CF06F_8F91_49EE_A5BB_381EF75062C8

#include "ccfake/base/ns.h"
#include <tuple>
#include <stddef.h>

CCFAKE_NS_BEGIN

template<typename T>
struct function_traits
: function_traits<decltype(&T::operator())>
{
};

template<typename ClassType, typename Arg>
struct function_traits<void (ClassType::*)(const Arg&) const>
{
    typedef Arg argument_type;
};

template<typename ClassType, typename Arg>
struct function_traits<void (ClassType::*)(Arg&) const>
{
    typedef Arg argument_type;
};

// XXX: below is the complete version!
template<typename ClassType, typename ReturnType, typename ... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
{
    enum {arity = sizeof ...(Args)};
    typedef ReturnType result_type;

    template<size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...> >::type type;
    };
};

#define CCFAKE_ARG_TYPE(LAMDA) typename ::CCFAKE_NS::function_traits<LAMDA>::argument_type

CCFAKE_NS_END

#endif

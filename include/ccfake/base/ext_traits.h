#ifndef CCFAKE_F25A2E8D_A775_44BF_88D1_166DFF56186A
#define CCFAKE_F25A2E8D_A775_44BF_88D1_166DFF56186A

#include "ccfake/base/ns.h"
#include <type_traits>

CCFAKE_NS_BEGIN

template<typename T, typename H>
using is_same_traits =
		typename std::enable_if<std::is_same_v<std::decay_t<T>, std::decay_t<H>>>::type;

template<typename T, typename H>
using is_not_same_traits =
		typename std::enable_if<std::negation_v<std::is_same<std::decay_t<T>, std::decay_t<H>>>>::type;

template<typename T, typename ...TS>
using all_same_traits =
		typename std::enable_if<std::conjunction<std::is_same<T, TS>...>::value>::type;

template<typename T, typename ...TS>
using all_same_or_empty_traits =
		typename std::enable_if<std::disjunction<std::bool_constant<not(sizeof...(TS))>,
		std::conjunction<std::is_same<T, TS>...>>::value>::type;

template<typename T, typename ...TS>
using all_convertible_traits =
		typename std::enable_if<std::conjunction<std::is_convertible<TS, T>...>::value>::type;

#define IS_SAME_CONCEPT(T, H)             is_same_traits<T, H>* = nullptr
#define IS_NOT_SAME_CONCEPT(T, H)         is_not_same_traits<T, H>* = nullptr
#define ALL_SAME_CONCEPT(TS, T)           all_same_traits<T, TS...>* = nullptr
#define ALL_SAME_OR_EMPTY_CONCEPT(TS, T)  all_same_or_empty_traits<T, TS...>* = nullptr
#define ALL_CONVERTIBLE_CONCEPT(TS, T)    all_convertible_traits<T, TS...>* = nullptr

CCFAKE_NS_END

#endif

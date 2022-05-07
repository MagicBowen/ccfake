#ifndef HCB177A07_555C_415C_B7E5_C20E0124CEE6
#define HCB177A07_555C_415C_B7E5_C20E0124CEE6

#include "ccfake/dtree/dtree_node_builder.h"

CCFAKE_NS_BEGIN

#define IS_DTREE_NODE public ::CCFAKE_NS::DtreeNode

#define DTREE_OF(TYPE, NAME, ...)      		\
std::unique_ptr<TYPE> NAME = ::CCFAKE_NS::DtreeNodeBuilder<TYPE>(#TYPE, ##__VA_ARGS__) * [](auto && self)

#define DTREE_NODE_OF(TYPE, ...)      		\
self + ::CCFAKE_NS::DtreeNodeBuilder<TYPE>(#TYPE, ##__VA_ARGS__) * [](auto && self)

#define DTREE_LEAF_OF(TYPE, ...)       		\
DTREE_NODE_OF(TYPE, ##__VA_ARGS__) {}

CCFAKE_NS_END

#endif

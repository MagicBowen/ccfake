#ifndef HCB177A07_555C_415C_B7E5_C20E0124CEE6
#define HCB177A07_555C_415C_B7E5_C20E0124CEE6

#include "ccfake/dtree/dtree_node_builder.h"

CCFAKE_NS_BEGIN

#define DTREE_NODE_TYPE(TYPE) struct TYPE : ::CCFAKE_NS::DtreeNode

#define DTREE_(TYPE, NAME, ...)        \
std::unique_ptr<TYPE> NAME = ::CCFAKE_NS::DtreeNodeBuilder<TYPE>(#TYPE, ##__VA_ARGS__) * [](auto && self)

#define NODE_(TYPE, ...)      		    \
self + ::CCFAKE_NS::DtreeNodeBuilder<TYPE>(#TYPE, ##__VA_ARGS__) * [](auto && self)

#define LEAF_(TYPE, ...)    NODE_(TYPE, ##__VA_ARGS__) {}

#define ATTR_(NAME, VALUE)  self.NAME = (VALUE)

#define DTREE_FIND(ROOT, TYPE) 	     ROOT->getNode<TYPE>()

#define DTREE_FIND_ROOT(NODE, TYPE)  NODE->getRootOf<TYPE>()

#define DTREE_FIND_BY(ROOT, TYPE, COND) \
		ROOT->getNodeBy<TYPE>([&](const auto& self) {return (COND);})


CCFAKE_NS_END

#endif

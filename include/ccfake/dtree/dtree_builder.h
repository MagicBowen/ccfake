#ifndef H186F2EF9_87DB_441E_BE95_7A8005BCCC83
#define H186F2EF9_87DB_441E_BE95_7A8005BCCC83

#include "ccfake/dtree/dtree_node_builder.h"

CCFAKE_NS_BEGIN

///////////////////////////////////////////////////////////
#define DTREE_NODE_TYPE(TYPE) 					\
		struct TYPE : ::CCFAKE_NS::DtreeNode

///////////////////////////////////////////////////////////
#define DTREE_OF(TYPE, NAME, ...)        		\
		std::unique_ptr<TYPE> NAME = 			\
		::CCFAKE_NS::DtreeNodeBuilder<TYPE>(#TYPE, ##__VA_ARGS__) \
		* [](auto && self)

///////////////////////////////////////////////////////////
#define DTREE_NODE_OF(TYPE, ...)      		    \
		self + 									\
		::CCFAKE_NS::DtreeNodeBuilder<TYPE>(#TYPE, ##__VA_ARGS__) \
		* [](auto && self)

///////////////////////////////////////////////////////////
#define DTREE_LEAF_OF(TYPE, ...)    			\
		DTREE_NODE_OF(TYPE, ##__VA_ARGS__) {}

///////////////////////////////////////////////////////////
#define DTREE_ATTR_OF(NAME, VALUE)  			\
		self.NAME = (VALUE)

///////////////////////////////////////////////////////////
#define DTREE_COND(COND) [&](const auto& self) {return (COND);}

CCFAKE_NS_END

#endif

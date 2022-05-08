#ifndef H186F2EF9_87DB_441E_BE95_7A8005BCCC83
#define H186F2EF9_87DB_441E_BE95_7A8005BCCC83

#include "ccfake/dtree/dtree_node.h"

CCFAKE_NS_BEGIN

template<typename NODE>
struct DtreeNodeBuilder {
	template<typename ...ATTR>
	explicit DtreeNodeBuilder(DtreeNode::Type type, ATTR&& ...attr)
	: node(new NODE(std::forward<ATTR>(attr)...)){
		node->updateType(type);
	}

	template<typename USER_BUILDER>
	auto build(USER_BUILDER && userBuilder) {
		std::forward<USER_BUILDER>(userBuilder)(*node);
		return std::move(node);
	}

private:
	std::unique_ptr<NODE> node;
};

///////////////////////////////////////////////////////////
template<typename NODE, typename USER_BUILDER>
auto operator* (DtreeNodeBuilder<NODE> &&nodeBuilder, USER_BUILDER && userBuilder) {
	return nodeBuilder.build(std::forward<USER_BUILDER>(userBuilder));
}

template<typename NODE> DtreeNode& operator+ (DtreeNode & root, NODE && node) {
	return root.add(std::forward<NODE>(node));
}

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

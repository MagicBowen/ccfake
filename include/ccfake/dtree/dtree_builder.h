#ifndef H186F2EF9_87DB_441E_BE95_7A8005BCCC83
#define H186F2EF9_87DB_441E_BE95_7A8005BCCC83

#include "ccfake/dtree/dtree_node.h"

CCFAKE_NS_BEGIN

template<typename NODE>
struct DtreeNodeBuilder {
	template<typename ...PARAs>
	explicit DtreeNodeBuilder(PARAs&& ...paras)
	: node(new NODE(std::forward<PARAs>(paras)...)){
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
#define CCFAKE_DTREE_NODE_TYPE(TYPE) 		    \
		struct TYPE : ::CCFAKE_NS::DtreeNode

///////////////////////////////////////////////////////////
#define CCFAKE_DTREE_OF(TYPE, NAME, ...)        \
		std::unique_ptr<TYPE> NAME = 			\
		::CCFAKE_NS::DtreeNodeBuilder<TYPE>(__VA_ARGS__) \
		* [](auto && self)

///////////////////////////////////////////////////////////
#define CCFAKE_DTREE_NODE_OF(TYPE, ...)      	\
		self + 									\
		::CCFAKE_NS::DtreeNodeBuilder<TYPE>(__VA_ARGS__) \
		* [](auto && self)

///////////////////////////////////////////////////////////
#define CCFAKE_DTREE_LEAF_OF(TYPE, ...)    		\
		CCFAKE_DTREE_NODE_OF(TYPE, ##__VA_ARGS__) {}

///////////////////////////////////////////////////////////
#define CCFAKE_DTREE_ATTR_OF(ATTR, VALUE)  		\
		self.ATTR = (VALUE)

///////////////////////////////////////////////////////////
#define CCFAKE_DTREE_ATTRS_OF(ATTR, ...)  		\
		self.ATTR = decltype(self.ATTR){__VA_ARGS__}

///////////////////////////////////////////////////////////
#define CCFAKE_DTREE_ATTR_SET(FUNC, VALUE)  	\
		self.FUNC(VALUE)

///////////////////////////////////////////////////////////
#define CCFAKE_DTREE_ATTRS_SET(FUNC, ...)  		\
		self.FUNC(__VA_ARGS__)

///////////////////////////////////////////////////////////
#define CCFAKE_DTREE_COND(COND) [&](const auto& self) {return (COND);}

CCFAKE_NS_END

#endif

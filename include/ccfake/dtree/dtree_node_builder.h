#ifndef HE9052F18_41A2_4F4C_ABF6_8DA7F04D72F8
#define HE9052F18_41A2_4F4C_ABF6_8DA7F04D72F8

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

template<typename NODE, typename USER_BUILDER>
auto operator* (DtreeNodeBuilder<NODE> &&nodeBuilder, USER_BUILDER && userBuilder) {
	return nodeBuilder.build(std::forward<USER_BUILDER>(userBuilder));
}

template<typename NODE> DtreeNode& operator+ (DtreeNode & root, NODE && node) {
	return root.add(std::forward<NODE>(node));
}

CCFAKE_NS_END

#endif

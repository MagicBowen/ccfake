#ifndef HD6F99730_E1DE_4A80_B35F_7FB7FDEB87EC
#define HD6F99730_E1DE_4A80_B35F_7FB7FDEB87EC

#include "ccfake/base/ns.h"
#include <string>
#include <memory>
#include <list>

CCFAKE_NS_BEGIN

struct DtreeNode {
	using Type = std::string;

	template<typename ROOT>
	ROOT* getSuperOf() {
		if (isTreeRoot()) return nullptr;
		auto result = dynamic_cast<ROOT*>(parent);
		return result ? result : parent->getSuperOf<ROOT>();
	}

	template<typename ROOT>
	const ROOT* getSuperOf() const {
		return const_cast<DtreeNode&>(*this).getSuperOf<ROOT>();
	}

	template<typename NODE, typename EQUAL>
	NODE* getLowerOf(const EQUAL& equal) {
		NODE *node = dynamic_cast<NODE*>(this);
		if (node && equal(*node)) return node;

		if (!hasChildren()) return nullptr;

		for (auto& child : children) {
			auto result = child->getLowerOf<NODE>(equal);
			if (result) return result;
		}
		return nullptr;
	}

	template<typename NODE, typename EQUAL>
	const NODE* getLowerOf(const EQUAL& equal) const {
		return const_cast<DtreeNode&>(*this).getLowerOf<NODE>(equal);
	}

	template<typename NODE>
	NODE* getLowerOf() {
		return getLowerOf<NODE>([](const auto& n) {return true;});
	}

	template<typename NODE>
	const NODE* getLowerOf() const {
		return const_cast<DtreeNode&>(*this).getLowerOf<NODE>();
	}

	virtual ~DtreeNode() = default;

private:
	bool isTreeRoot() const {
		return parent == nullptr;
	}

	bool hasChildren() const {
		return !children.empty();
	}

private:
	friend struct Dtree;
	template<typename NODE> friend struct DtreeNodeBuilder;
	template<typename NODE> friend DtreeNode& operator+ (DtreeNode& root, NODE&&);

	void updateType(Type type) {
		this->type = type;
	}

	template<typename NODE_PTR>
	auto& add(NODE_PTR && node) {
		node->parent = this;
		children.emplace_back(std::forward<NODE_PTR>(node));
		return *this;
	}

private:
	using Ptr = std::unique_ptr<DtreeNode>;
	using DtreeNodeChildren = std::list<Ptr>;

	Type type{"DtreeNode"};
	DtreeNode *parent{nullptr};
	DtreeNodeChildren children;
};

CCFAKE_NS_END

#endif

#ifndef HD6F99730_E1DE_4A80_B35F_7FB7FDEB87EC
#define HD6F99730_E1DE_4A80_B35F_7FB7FDEB87EC

#include "ccfake/dtree/dtree_visitor.h"
#include <string>
#include <memory>
#include <vector>
#include <list>

CCFAKE_NS_BEGIN

struct DtreeNode {
	using Type = std::string;

	Type getType() const {
		return type;
	}

	virtual ~DtreeNode() = default;

protected:
	template<typename ROOT>
	ROOT* getSuperOf() {
		if (isTreeRoot()) return nullptr;
		auto result = dynamic_cast<ROOT*>(parent);
		return result ? result : parent->getSuperOf<ROOT>();
	}

	template<typename ROOT>
	const ROOT* getSuperOf() const {
		return const_cast<DtreeNode*>(this)->getSuperOf<ROOT>();
	}

	template<typename NODE, typename COND>
	NODE* getLowerOf(const COND& cond) {
		NODE *node = dynamic_cast<NODE*>(this);
		if (node && cond(*node)) return node;

		if (!hasChildren()) return nullptr;

		for (auto& child : children) {
			auto result = child->getLowerOf<NODE>(cond);
			if (result) return result;
		}
		return nullptr;
	}

	template<typename NODE, typename COND>
	const NODE* getLowerOf(const COND& cond) const {
		return const_cast<DtreeNode*>(this)->getLowerOf<NODE>(cond);
	}

	template<typename NODE>
	NODE* getLowerOf() {
		return getLowerOf<NODE>([](const auto& n) {return true;});
	}

	template<typename NODE>
	const NODE* getLowerOf() const {
		return const_cast<DtreeNode*>(this)->getLowerOf<NODE>();
	}

	template<typename NODE, typename COND>
	std::vector<NODE*> getLowerOfAll(const COND& cond) {
		std::vector<NODE*> result;
		getAllLowerNodesBy(cond, result);
		return result;
	}

	template<typename NODE, typename COND>
	const std::vector<NODE*> getLowerOfAll(const COND& cond) const {
		return const_cast<DtreeNode*>(this)->getLowerOfAll<NODE>(cond);
	}

	template<typename NODE>
	std::vector<NODE*> getLowerOfAll() {
		return getLowerOfAll<NODE>([](const auto& n) {return true;});
	}

	template<typename NODE>
	const std::vector<NODE*> getLowerOfAll() const {
		return const_cast<DtreeNode*>(this)->getLowerOfAll<NODE>();
	}

private:
	template<typename NODE, typename COND>
	void getAllLowerNodesBy(const COND& cond, std::vector<NODE*>& result) {
		NODE *node = dynamic_cast<NODE*>(this);
		if (node && cond(*node)) {
			result.push_back(node);
		}

		if (!hasChildren()) return;

		for (auto& child : children) {
			child->getAllLowerNodesBy<>(cond, result);
		}
	}

private:
	friend struct Dtree;
	template<typename NODE> friend struct DtreeNodeBuilder;
	template<typename NODE> friend DtreeNode& operator+ (DtreeNode& root, NODE&&);

	template<typename NODE_PTR>
	auto& add(NODE_PTR && node) {
		node->parent = this;
		children.emplace_back(std::forward<NODE_PTR>(node));
		return *this;
	}

	Status accept(DtreeVisitor& visitor) {
		Status status = visitor.visitNode(*this);
		if (status_is_failed(status) || status_is_done(status)) {
			return status;
		}

		for (auto& child : children) {
			status = child->accept(visitor);
			if (status_is_failed(status) || status_is_done(status)) {
				return status;
			}
		}
		return Status::SUCCESS;
	}

	Status accept(DtreeVisitor& visitor) const {
		return const_cast<DtreeNode*>(this)->accept(visitor);
	}

	void updateType(Type type) {
		this->type = type;
	}

	bool isTreeRoot() const {
		return parent == nullptr;
	}

	bool hasChildren() const {
		return !children.empty();
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

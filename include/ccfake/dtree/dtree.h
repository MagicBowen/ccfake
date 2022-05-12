#ifndef HCB177A07_555C_415C_B7E5_C20E0124CEE6
#define HCB177A07_555C_415C_B7E5_C20E0124CEE6

#include "ccfake/dtree/dtree_builder.h"
#include "ccfake/log/log.h"

CCFAKE_NS_BEGIN

struct Dtree {
	Dtree(DtreeNode& node)
	: dtree{&node} {
	}

	Dtree(DtreeNode* pnode) {
		if (!pnode) {
			CCFAKE_FATAL("Dtree constructed by nullptr!");
		}
		dtree = pnode;
	}

	Dtree(DtreeNode::Ptr& pnode) {
		if (!pnode) {
			CCFAKE_FATAL("Dtree constructed by invalid ptr!");
		}
		dtree = pnode.get();
	}
	template<typename NODE>
	Dtree(std::unique_ptr<NODE> & pnode) {
		if (!pnode) {
			CCFAKE_FATAL("Dtree constructed by invalid ptr!");
		}
		dtree = pnode.get();
	}

	template<typename NODE>
	NODE* get() {
		return dtree->getLowerOf<NODE>();
	}

	template<typename NODE, typename COND>
	NODE* get(const COND& cond) {
		return dtree->getLowerOf<NODE>(cond);
	}

	template<typename NODE>
	std::vector<NODE*> getAll() {
		return dtree->getLowerOfAll<NODE>();
	}

	template<typename NODE, typename COND>
	std::vector<NODE*> getAll(const COND& cond) {
		return dtree->getLowerOfAll<NODE>(cond);
	}

	template<typename ROOT>
	ROOT* getRoot() {
		return dtree->getSuperOf<ROOT>();
	}

	Status accept(DtreeVisitor& visitor,
			DtreeVisitOrder order = DtreeVisitOrder::TOP_DOWN) {

		if (status_is_failed(visitor.visitBegin(*dtree))) return Status::FAILURE;
		if (status_is_failed(dtree->accept(visitor, order))) return Status::FAILURE;
		if (status_is_failed(visitor.visitEnd(*dtree))) return Status::FAILURE;

		return Status::SUCCESS;
	}

	Status accept(const DtreeVisitor& visitor,
			DtreeVisitOrder order = DtreeVisitOrder::TOP_DOWN) {

		return accept(*const_cast<DtreeVisitor*>(&visitor), order);
	}

private:
	DtreeNode* dtree;
};

CCFAKE_NS_END

#endif

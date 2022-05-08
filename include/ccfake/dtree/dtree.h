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

	template<typename ROOT>
	ROOT* getRoot() {
		return dtree->getSuperOf<ROOT>();
	}

private:
	DtreeNode* dtree;
};

CCFAKE_NS_END

#endif

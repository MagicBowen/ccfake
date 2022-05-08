#ifndef H404B5898_8DD3_426E_96F3_9E9CE680CFBD
#define H404B5898_8DD3_426E_96F3_9E9CE680CFBD

#include "ccfake/base/status.h"

CCFAKE_NS_BEGIN

struct DtreeNode;

struct DtreeVisitor {
	virtual Status visitBegin(DtreeNode&) {
		return Status::SUCCESS;
	}

	virtual Status visitEnd(DtreeNode&) {
		return Status::SUCCESS;
	}

	virtual Status visitNode(DtreeNode&) {
		return Status::SUCCESS;
	}
	virtual ~DtreeVisitor() = default;
};

CCFAKE_NS_END

#endif

#ifndef H1A557B9B_F47C_4428_A93B_4F4600D2D5E1
#define H1A557B9B_F47C_4428_A93B_4F4600D2D5E1

#include "ccfake/dtree/dtree_visitor.h"
#include "ccfake/log/log.h"

CCFAKE_NS_BEGIN

template<typename NODE_INTF>
struct DtreeExecutor : DtreeVisitor {
private:
	OVERRIDE(Status visitBegin(DtreeNode& dtreeNode)) {
		return executeBegin(castToIntf(dtreeNode));
	}

	OVERRIDE(Status visitEnd(DtreeNode& dtreeNode)) {
		return executeEnd(castToIntf(dtreeNode));
	}

	OVERRIDE(Status visitNode(DtreeNode& dtreeNode)) {
		return execute(castToIntf(dtreeNode));
	}

private:
	NODE_INTF& castToIntf(DtreeNode& dtreeNode) {
		NODE_INTF* intf = dynamic_cast<NODE_INTF*>(&dtreeNode);
		if (!intf) {
			CCFAKE_FATAL("Unsuported dtree node interface!");
		}
		return *intf;
	}

private:
	DEFAULT(Status, executeBegin(NODE_INTF&));
	DEFAULT(Status, executeEnd(NODE_INTF&));
	DEFAULT(Status, execute(NODE_INTF&));
};

CCFAKE_NS_END

#endif

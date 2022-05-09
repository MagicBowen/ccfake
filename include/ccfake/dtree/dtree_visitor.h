#ifndef H404B5898_8DD3_426E_96F3_9E9CE680CFBD
#define H404B5898_8DD3_426E_96F3_9E9CE680CFBD

#include "ccfake/base/keyword.h"
#include "ccfake/base/status.h"

CCFAKE_NS_BEGIN

struct DtreeNode;

INTERFACE(DtreeVisitor) {
	DEFAULT(Status, visitBegin(DtreeNode&));
	DEFAULT(Status, visitEnd(DtreeNode&));
	DEFAULT(Status, visitNode(DtreeNode&));
};

CCFAKE_NS_END

#endif

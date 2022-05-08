#ifndef H404B5898_8DD3_426E_96F3_9E9CE680CFBD
#define H404B5898_8DD3_426E_96F3_9E9CE680CFBD

#include "ccfake/base/keyword.h"
#include "ccfake/base/status.h"

CCFAKE_NS_BEGIN

struct DtreeNode;

template<typename NODE>
struct DtreeVisitor {
	DEFAULT(Status, visitBegin(NODE&));
	DEFAULT(Status, visitEnd(NODE&));
	DEFAULT(Status, visitNode(NODE&));
	virtual ~DtreeVisitor() = default;
};

CCFAKE_NS_END

#endif

#ifndef H4DF10F2F_C53C_4C8F_912F_76730E3B48D7
#define H4DF10F2F_C53C_4C8F_912F_76730E3B48D7

#include "ccfake/dtree/dtree_visitor.h"

CCFAKE_NS_BEGIN

#define DTREE_NODE_DISPATCH_FOR(NODE)  			\
for (DtreeNode *_pnode = &node; _pnode; _pnode = nullptr)

#define DTREE_NODE_DISPATCH(TYPE, FUNC)  		\
if (_pnode->getType() == #TYPE) {				\
	return FUNC(*dynamic_cast<TYPE*>(_pnode));	\
}

CCFAKE_NS_END

#endif

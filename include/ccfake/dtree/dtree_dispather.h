#ifndef H19D6F691_3EF6_4F19_9F95_8F47C7918DEF
#define H19D6F691_3EF6_4F19_9F95_8F47C7918DEF

#include "ccfake/dtree/dtree_node.h"

CCFAKE_NS_BEGIN

#define DTREE_NODE_DISPATH_BEGIN(NODE)  				\
	for (::CCFAKE_NS::DtreeNode *pnode = &NODE; true;) {

#define DTREE_NODE_DISPATH_END()  						\
	break;    }

#define DTREE_NODE_DISPATH(TYPE, HANDLE)				\
	if (pnode->getType() == std::string(#TYPE)) {		\
	    return HANDLE(*dynamic_cast<TYPE*>(pnode));		\
	}

CCFAKE_NS_END

#endif

#ifndef H4DF10F2F_C53C_4C8F_912F_76730E3B48D7
#define H4DF10F2F_C53C_4C8F_912F_76730E3B48D7

#include "ccfake/dtree/dtree_visitor.h"

CCFAKE_NS_BEGIN

namespace detail {
	template<typename NODE_TYPE, typename ...NODE_TYPES>
	struct DtreeNodeMatcher {
		template<typename HANDLE>
		Status operator() (DtreeNode* node, HANDLE && handle) {
			if (!node) return Status::FAILURE;
			if (auto pnode = dynamic_cast<NODE_TYPE*>(node); pnode) {
				return std::forward<HANDLE>(handle)(*pnode);
			}
			return DtreeNodeMatcher<NODE_TYPES...>()(node, std::forward<HANDLE>(handle));
		}
	};

	template<>
	struct DtreeNodeMatcher<void> {
		template<typename HANDLE>
		Status operator() (DtreeNode* node, HANDLE &&) {
			return Status::SUCCESS;
		}
	};
}

////////////////////////////////////////////////////////////
#define CCFAKE_DTREE_MATCH_FOR(NODE)  					\
for (auto *_pnode = &NODE; _pnode; _pnode = nullptr)

#define CCFAKE_DTREE_NODE_MATCH(TYPE, HANDLE)  			\
if (auto nodep = dynamic_cast<TYPE*>(_pnode); nodep) { 	\
	return HANDLE(*nodep);								\
}

////////////////////////////////////////////////////////////
#define CCFAKE_DTREE_MATCH(NODE, HANDLE, ...)			\
::CCFAKE_NS::detail::DtreeNodeMatcher<__VA_ARGS__, void>()(&(NODE), [&](auto & node) {	\
	return HANDLE(node);								\
})

CCFAKE_NS_END

#endif

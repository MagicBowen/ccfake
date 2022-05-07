#ifndef CCFAKE_079D3C0C_1D82_403B_91DE_E449C4893172
#define CCFAKE_079D3C0C_1D82_403B_91DE_E449C4893172

#include "ccfake/base/ns.h"
#include <algorithm>

CCFAKE_NS_BEGIN

template<typename CONTAINER>
bool container_is_equal(const CONTAINER& lhs, const CONTAINER& rhs) {
	if (lhs.size() != rhs.size()) return false;
	for (auto item : lhs) {
		auto result = std::find_if(rhs.cbegin(), rhs.cend(), [&item](const auto& other) {
			return item == other;
		});
		if (result == rhs.end()) return false;
	}
	return true;
}

CCFAKE_NS_END

#endif

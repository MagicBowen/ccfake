#ifndef H3C2CD904_6F62_4A2E_85F8_33608012903B
#define H3C2CD904_6F62_4A2E_85F8_33608012903B

#include "ccfake/dtree/dtree.h"
#include <string>

CCFAKE_NS_BEGIN

struct Device : ::CCFAKE_NS::DtreeNode {
};

DTREE_NODE_TYPE(Modem) {
	Modem(int id)
	: id{id} {
	}


	int id;
	std::string ratMode;
};

DTREE_NODE_TYPE(Band) {
	Band(int id, std::string mode)
	: id{id}, ratMode{mode} {
	}

	int id;
	std::string ratMode;
};

DTREE_NODE_TYPE(RxProtect) {
	RxProtect(int id) : id{id} {
	}

	int id;
	std::string name;
};

CCFAKE_NS_END

#endif

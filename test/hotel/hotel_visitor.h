#ifndef HF2033EE1_2087_4E57_B8A4_DD23BC2D3251
#define HF2033EE1_2087_4E57_B8A4_DD23BC2D3251

#include "ccfake/dtree/dtree_visitor.h"
#include "hotel/hotel.h"
#include <stdio.h>

CCFAKE_NS_BEGIN

struct HotelLayoutVisitor : DtreeVisitor<HotelNode> {
private:
	OVERRIDE(Status visitBegin(HotelNode& node)) {
		printf("========= Hotel Layout ==========\n");
		return Status::SUCCESS;
	}
	OVERRIDE(Status visitEnd(HotelNode& node)) {
		printf("=================================\n");
		return Status::SUCCESS;
	}
	OVERRIDE(Status visitNode(HotelNode& node)) {
		node.layout();
		return Status::SUCCESS;
	}
};

struct HotelCloseVisitor : DtreeVisitor<HotelNode> {
private:
	OVERRIDE(Status visitNode(HotelNode& node)) {
		node.close();
		return Status::SUCCESS;
	}
};

CCFAKE_NS_END

#endif

#ifndef HF2033EE1_2087_4E57_B8A4_DD23BC2D3251
#define HF2033EE1_2087_4E57_B8A4_DD23BC2D3251

#include "ccfake/dtree/dtree_executor.h"
#include "hotel/hotel.h"
#include <stdio.h>

CCFAKE_NS_BEGIN

struct HotelLayoutExecutor : DtreeExecutor<HotelNode> {
private:
	OVERRIDE(Status executeBegin(HotelNode& node)) {
		printf("========= Hotel Layout ==========\n");
		return Status::SUCCESS;
	}
	OVERRIDE(Status executeEnd(HotelNode& node)) {
		printf("=================================\n");
		return Status::SUCCESS;
	}
	OVERRIDE(Status execute(HotelNode& node)) {
		node.layout();
		return Status::SUCCESS;
	}
};

CCFAKE_NS_END

#endif

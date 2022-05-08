#ifndef HF2033EE1_2087_4E57_B8A4_DD23BC2D3251
#define HF2033EE1_2087_4E57_B8A4_DD23BC2D3251

#include "ccfake/dtree/dtree_visitor.h"
#include "ccfake/dtree/dtree_dispather.h"
#include "hotel/hotel.h"
#include <stdio.h>

CCFAKE_NS_BEGIN

#define DTREE_NODE_LAYOUT(TYPE) DTREE_NODE_DISPATH(TYPE, layout)

struct HotelLayoutVisitor : DtreeVisitor {
private:
	Status visitBegin(DtreeNode& node) override {
		printf("========= Hotel Layout ==========\n");
		return Status::SUCCESS;
	}
	Status visitEnd(DtreeNode& node) override {
		printf("=================================\n");
		return Status::SUCCESS;
	}
	Status visitNode(DtreeNode& node) override {
		DTREE_NODE_DISPATH_BEGIN(node)
			DTREE_NODE_LAYOUT(Hotel);
			DTREE_NODE_LAYOUT(Lobby);
			DTREE_NODE_LAYOUT(Floor);
			DTREE_NODE_LAYOUT(Room);
			DTREE_NODE_LAYOUT(MeetingRoom);
			DTREE_NODE_LAYOUT(Restaurant);
		DTREE_NODE_DISPATH_END()
		return Status::SUCCESS;
	}

private:
	Status layout(const Hotel& hotel) {
		printf("Hotel : name(%s), address(%s)\n",
				hotel.name.c_str(), hotel.address.c_str());
		return Status::SUCCESS;
	}
	Status layout(const Lobby& lobby) {
		printf("Lobby : staffNum(%d)\n", lobby.staffNum);
		return Status::SUCCESS;
	}
	Status layout(const Floor& floor) {
		printf("Floor : floorNo(%d)\n", floor.floorNo);
		return Status::SUCCESS;
	}
	Status layout(const Room& room) {
		printf("Room : roomNo(%d), guest(%s)\n", room.roomNo, room.guestName.c_str());
		return Status::SUCCESS;
	}
	Status layout(const MeetingRoom& meetingRoom) {
		printf("MeetingRoom : roomNo(%d), capacity(%d)\n",
				meetingRoom.roomNo, meetingRoom.capacity);
		return Status::SUCCESS;
	}
	Status layout(const Restaurant& restaurant) {
		printf("Restaurant : name(%s)\n", restaurant.name.c_str());
		return Status::SUCCESS;
	}
};

CCFAKE_NS_END

#endif

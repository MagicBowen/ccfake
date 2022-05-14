#ifndef H2A3537BF_E003_47D0_B185_6932ECF4095B
#define H2A3537BF_E003_47D0_B185_6932ECF4095B

#include "ccfake/dtree/dtree_matcher.h"
#include "hotel/hotel.h"

CCFAKE_NS_BEGIN

struct HotelCloseVisitor : DtreeVisitor {
private:
	OVERRIDE(Status visitNode(DtreeNode& node)) {
		return CCFAKE_DTREE_MATCH(node, close, Lobby, Room, MeetingRoom);
	}

private:
	Status close(Lobby &lobby) {
		lobby.staffNum= 0;
		return Status::SUCCESS;
	}

	Status close(Room &room) {
		room.checkOut();
		return Status::SUCCESS;
	}

	Status close(MeetingRoom &room) {
		room.hasBooked= false;
		room.capacity= 0;
		return Status::SUCCESS;
	}
};

CCFAKE_NS_END

#endif

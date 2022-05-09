#ifndef HC3EF054A_92ED_4AD8_A08E_6BD4A8D550B3
#define HC3EF054A_92ED_4AD8_A08E_6BD4A8D550B3

#include "ccfake/dtree/dtree_dispatcher.h"
#include "hotel/hotel.h"

CCFAKE_NS_BEGIN

struct HotelReserveVisitor : DtreeVisitor {
	HotelReserveVisitor(const std::string& customerName)
	: customerName{customerName} {
	}

	RoomNo getReservedRoomNo() const {
		return roomNo;
	}

private:
	OVERRIDE(Status visitNode(DtreeNode& node)) {
		DTREE_NODE_DISPATCH_FOR(node) {
			DTREE_NODE_DISPATCH(Room,  reserve);
		}
		return Status::SUCCESS;
	}

private:
	Status reserve(Room &room) {
		if (room.hasBooked) return Status::SUCCESS;
		room.checkIn(customerName);
		this->roomNo = room.roomNo;
		return Status::DONE;
	}

private:
	const std::string customerName;
	RoomNo roomNo{0};
};

CCFAKE_NS_END

#endif

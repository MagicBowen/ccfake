#ifndef HBE55842B_720A_438F_AC29_BB0BCA9A2753
#define HBE55842B_720A_438F_AC29_BB0BCA9A2753

#include "ccfake/dtree/dtree.h"

DTREE_NODE_TYPE(Hotel) {
	Hotel(std::string name)
			: name{name} {
	}

	std::string address{""};
	std::string name;
};

DTREE_NODE_TYPE(Lobby) {
	unsigned int staffNum{1};
};

DTREE_NODE_TYPE(Floor) {
	Floor(unsigned int floorNo)
			: floorNo{floorNo} {
	}

	unsigned int floorNo;
};

DTREE_NODE_TYPE(Room) {
	Room(unsigned int roomNo)
			: roomNo{roomNo} {
	}

	void CheckIn(std::string guestName) {
		this->guestName = guestName;
		this->hasBooked = true;
	}

	void CheckOut() {
		this->guestName = "";
		this->hasBooked = false;
	}

	bool hasBooked{false};
	std::string guestName;
	unsigned int roomNo;
};

DTREE_NODE_TYPE(MeetingRoom) {
	MeetingRoom(unsigned int roomNo)
			: roomNo{roomNo} {
	}

	unsigned int capacity{0};
	unsigned int roomNo;
};

DTREE_NODE_TYPE(Restaurant) {
	Restaurant(std::string name)
			: name{name} {
	}

	std::string name;
};

#define HOTEL(NAME) 				DTREE_OF(Hotel, NAME, #NAME)
#define LOBBY()     				DTREE_NODE_OF(Lobby)
#define FLOOR(NO)     				DTREE_NODE_OF(Floor, NO)
#define ROOM(NO)      				DTREE_NODE_OF(Room, NO)
#define MEETING_ROOM(NO)  			DTREE_NODE_OF(MeetingRoom, NO)
#define RESTAURANT(NAME)            DTREE_LEAF_OF(Restaurant, NAME)
#define ATTR(NAME, VALUE)           DTREE_ATTR_OF(NAME, VALUE)

#endif

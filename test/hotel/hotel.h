#ifndef HBE55842B_720A_438F_AC29_BB0BCA9A2753
#define HBE55842B_720A_438F_AC29_BB0BCA9A2753

#include "ccfake/dtree/dtree.h"

DTREE_NODE_TYPE(Hotel) {
	Hotel(std::string name)
			: name{name} {
	}

	std::string address{""};

private:
	std::string name;
};

DTREE_NODE_TYPE(Lobby) {
	unsigned int staffNum{1};
};

DTREE_NODE_TYPE(Floor) {
	Floor(unsigned int floorNo)
			: floorNo{floorNo} {
	}

	unsigned int FloorNo() const {
		return floorNo;
	}

private:
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

	unsigned int RoomNo() const {
		return roomNo;
	}

	void RoomNo(unsigned int roomNo) {
		this->roomNo = roomNo;
	}

	bool hasBooked{false};
	std::string guestName;

private:
	unsigned int roomNo;
};

DTREE_NODE_TYPE(MeetingRoom) {
	MeetingRoom(unsigned int roomNo)
			: roomNo{roomNo} {
	}

	unsigned int capacity{0};

private:
	unsigned int roomNo;
};

DTREE_NODE_TYPE(Restaurant) {
	Restaurant(std::string name)
			: name{name} {
	}

	std::string Name() const {
		return this->name;
	}

private:
	std::string name;
};

#define ATTR(NAME, VALUE)           ATTR_(NAME, VALUE)
#define HOTEL(NAME) 				DTREE_(Hotel, NAME, #NAME)
#define LOBBY()     				NODE_(Lobby)
#define FLOOR(NO)     				NODE_(Floor, NO)
#define ROOM(NO)      				NODE_(Room, NO)
#define MEETING_ROOM(NO)  			NODE_(MeetingRoom, NO)
#define RESTAURANT(NAME)            LEAF_(Restaurant, NAME)

#endif

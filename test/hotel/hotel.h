#ifndef HBE55842B_720A_438F_AC29_BB0BCA9A2753
#define HBE55842B_720A_438F_AC29_BB0BCA9A2753

#include "ccfake/dtree/dtree.h"

DTREE_NODE_TYPE(HotelNode) {
	DEFAULT(void, layout() const);
	DEFAULT(void, close());
};

class Hotel : public HotelNode {
public:
	std::string name;
	std::string address{""};

public:
	Hotel(std::string name)
			: name{name} {
	}

private:
	OVERRIDE(void layout() const) {
		printf("Hotel : name(%s), address(%s)\n",
				name.c_str(), address.c_str());
	}
};

class Lobby : public HotelNode {
public:
	unsigned int staffNum{1};

private:
	OVERRIDE(void layout() const) {
		printf("Lobby : staffNum(%d)\n", staffNum);
	}

	OVERRIDE(void close()) {
		staffNum = 0;
	}
};

class Floor : public HotelNode {
public:
	unsigned int floorNo;

public:
	Floor(unsigned int floorNo)
			: floorNo{floorNo} {
	}

private:
	OVERRIDE(void layout() const) {
		printf("Floor : floorNo(%d)\n", floorNo);
	}
};

using RoomNo = unsigned int;

class Room : public HotelNode {
public:
	RoomNo roomNo;
	bool hasBooked{false};
	std::string guestName;

public:
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

private:
	OVERRIDE(void layout() const) {
		printf("Room : roomNo(%d), guest(%s)\n",
				roomNo, guestName.c_str());
	}

	OVERRIDE(void close()) {
		CheckOut();
	}
};

class MeetingRoom : public HotelNode {
public:
	RoomNo roomNo;
	unsigned int capacity{0};

public:
	MeetingRoom(unsigned int roomNo)
			: roomNo{roomNo} {
	}

private:
	OVERRIDE(void layout() const) {
		printf("MeetingRoom : roomNo(%d), capacity(%d)\n",
			    roomNo, capacity);
	}

	OVERRIDE(void close()) {
		capacity = 0;
	}
};

class Restaurant : public HotelNode {
public:
	std::string name;

public:
	Restaurant(std::string name)
			: name{name} {
	}

private:
	OVERRIDE(void layout() const) {
		printf("Restaurant : name(%s)\n", name.c_str());
	}
};

#define HOTEL(NAME) 				DTREE_OF(Hotel, NAME, #NAME)
#define LOBBY()     				DTREE_NODE_OF(Lobby)
#define FLOOR(NO)     				DTREE_NODE_OF(Floor, NO)
#define ROOM(NO)      				DTREE_NODE_OF(Room, NO)
#define MEETING_ROOM(NO)  			DTREE_NODE_OF(MeetingRoom, NO)
#define RESTAURANT(NAME)            DTREE_LEAF_OF(Restaurant, NAME)
#define ATTR(NAME, VALUE)           DTREE_ATTR_OF(NAME, VALUE)

#endif

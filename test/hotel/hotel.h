#ifndef HBE55842B_720A_438F_AC29_BB0BCA9A2753
#define HBE55842B_720A_438F_AC29_BB0BCA9A2753

#include "ccfake/dtree/dtree.h"
#include "ccfake/base/status.h"
#include "hotel/mail.h"

using ccfake::Status;

CCFAKE_DTREE_NODE_TYPE(HotelNode) {
	DEFAULT(void, layout() const);
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

	void checkIn(std::string guestName) {
		this->guestName = guestName;
		this->hasBooked = true;
	}

	void checkOut() {
		this->guestName = "";
		this->hasBooked = false;
	}

private:
	OVERRIDE(void layout() const) {
		printf("Room : roomNo(%d), guest(%s)\n",
				roomNo, guestName.c_str());
	}
};

class MeetingRoom : public HotelNode {
public:
	RoomNo roomNo;
	bool hasBooked{false};
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

class MailBox : public HotelNode {
public:
	std::size_t capacity{2};

public:
	Status submitMail(const Mail& mail) {
		if (getMailCount() >=  capacity) {
			return Status::FAILURE;
		}
		mails.push_back(mail);
		return Status::SUCCESS;
	}

	Status fetchMail(Mail& mail) {
		if (getMailCount() ==  0) {
			return Status::FAILURE;
		}
		mail = *mails.begin();
		mails.pop_front();
		return Status::SUCCESS;
	}

	std::size_t getMailCount() const {
		return mails.size();
	}

private:
	OVERRIDE(void layout() const) {
		printf("MailBox : count(%lu)\n", mails.size());
	}

private:
	std::list<Mail> mails;
};

#define HOTEL(NAME) 				CCFAKE_DTREE_OF(Hotel, NAME, #NAME)
#define LOBBY     				    CCFAKE_DTREE_NODE_OF(Lobby)
#define MAIL_BOX     				CCFAKE_DTREE_NODE_OF(MailBox)
#define FLOOR(NO)     				CCFAKE_DTREE_NODE_OF(Floor, NO)
#define ROOM(NO)      				CCFAKE_DTREE_NODE_OF(Room, NO)
#define MEETING_ROOM(NO)  			CCFAKE_DTREE_NODE_OF(MeetingRoom, NO)
#define RESTAURANT(NAME)            CCFAKE_DTREE_LEAF_OF(Restaurant, NAME)
#define ATTR(NAME, VALUE)           CCFAKE_DTREE_ATTR_OF(NAME, VALUE)

#endif

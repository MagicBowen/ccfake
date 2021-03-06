#include "catch2/catch.hpp"
#include "hotel/hotel.h"
#include "hotel/hotel_layout.h"
#include "hotel/hotel_close.h"
#include "hotel/hotel_reserve.h"

CCFAKE_NS_USING;

TEST_CASE("Hotel Test") {

	HOTEL(Amber) {
		LOBBY {
			ATTR(staffNum, 2);
		};
		FLOOR(1) {
			ROOM(101) {
				ATTR(hasBooked, false);
			};
			ROOM(102) {
				ATTR(hasBooked, true);
				ATTR(guestName, "Jack");
			};
			MEETING_ROOM(103) {
				ATTR(capacity, 20);
			};
		};
		FLOOR(2) {
			ROOM(201) {
				ATTR(hasBooked, true);
				ATTR(guestName, "Robin");
			};
			RESTAURANT("cafeteria");
		};
	};

	SECTION("find unexisted room") {
		auto result = Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 103));
		REQUIRE(result == nullptr);
	};

	SECTION("find booked room") {
		auto result = Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 102));

		REQUIRE(result != nullptr);
		REQUIRE(result->hasBooked);
		REQUIRE(result->guestName == "Jack");
	};

	SECTION("find restaurant") {
		auto result = Dtree(Amber).get<Restaurant>();

		REQUIRE(result != nullptr);
		REQUIRE(result->name == "cafeteria");
	};

	SECTION("find in floor") {
		auto floor1 = Dtree(Amber).get<Floor>(CCFAKE_DTREE_COND(self.floorNo == 1));
		REQUIRE(floor1 != nullptr);

		auto floor2 = Dtree(Amber).get<Floor>(CCFAKE_DTREE_COND(self.floorNo == 2));
		REQUIRE(floor2 != nullptr);

		SECTION("find room in floor") {
			auto result = Dtree(floor1).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 102));
			REQUIRE(result != nullptr);
			REQUIRE(result->guestName == "Jack");
		}

		SECTION("find room not in current floor") {
			auto result = Dtree(floor1).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 201));
			REQUIRE(result == nullptr);
		}

		SECTION("find restaurant not in current floor") {
			auto result = Dtree(floor1).get<Restaurant>();
			REQUIRE(result == nullptr);
		}

		SECTION("find restaurant not in current floor") {
			auto result = Dtree(floor2).get<Restaurant>();
			REQUIRE(result != nullptr);
			REQUIRE(result->name == "cafeteria");
		}
	}

	SECTION("find floor by room") {
		auto room = Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 102));
		auto floor = Dtree(room).getRoot<Floor>();

		REQUIRE(floor != nullptr);
		REQUIRE(floor->floorNo == 1);
	}

	SECTION("find all rooms in hotel") {
		auto rooms = Dtree(Amber).getAll<Room>();

		REQUIRE(rooms.size() == 3);
		REQUIRE(rooms[0]->roomNo == 101);
		REQUIRE(rooms[1]->roomNo == 102);
		REQUIRE(rooms[2]->roomNo == 201);
	}

	SECTION("find all rooms checked in") {
		auto rooms = Dtree(Amber).getAll<Room>(CCFAKE_DTREE_COND(self.hasBooked));

		REQUIRE(rooms.size() == 2);
		REQUIRE(rooms[0]->roomNo == 102);
		REQUIRE(rooms[1]->roomNo == 201);
	}

	SECTION("check in and checkout room") {
		auto room201 = Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 201));

		REQUIRE(room201 != nullptr);
		REQUIRE(room201->hasBooked);
		REQUIRE(room201->guestName == "Robin");

		SECTION("checkout room") {
			room201->checkOut();
			REQUIRE(!Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 201))->hasBooked);

			SECTION("checkin room") {
				Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 201))->checkIn("Bowen");

				REQUIRE(room201->hasBooked);
				REQUIRE(room201->guestName == "Bowen");
			}
		}
	}

	SECTION("reserve room") {
		HotelReserveVisitor visitor{"Jerry"};
		Dtree(Amber).accept(visitor);

		REQUIRE(visitor.getReservedRoomNo() == 101);
		REQUIRE(Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 101))->hasBooked);
		REQUIRE(Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 101))->guestName == "Jerry");
		REQUIRE(Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 102))->guestName == "Jack");
	}

	SECTION("close and layout hotel by visitor") {
		Dtree(Amber).accept(HotelCloseVisitor{});

		REQUIRE(!Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 102))->hasBooked);
		REQUIRE(!Dtree(Amber).get<Room>(CCFAKE_DTREE_COND(self.roomNo == 201))->hasBooked);
		REQUIRE(Dtree(Amber).get<Lobby>()->staffNum == 0);
		REQUIRE(Dtree(Amber).get<MeetingRoom>()->capacity == 0);

		Dtree(Amber).accept(HotelLayoutExecutor{});
	}
}

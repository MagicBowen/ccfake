#include "catch2/catch.hpp"
#include "ccfake/ccfake.h"
#include "hotel/customer.h"
#include "hotel/hotel.h"

CCFAKE_NS_USING;

std::string HOTEL_NAME;
std::string HOTEL_ADDR;

TEST_CASE("Customer Test") {

	HOTEL(Amber) {
		ATTR(address, "ShangHai");

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

	Customer customer{"Bowen", *Amber};

	SECTION("send mail to hotel") {
		customer.send([&](Mail &mail) {
			mail.hotelName = Dtree(Amber).get<Hotel>()->name;
			mail.hotelAddress = Dtree(Amber).get<Hotel>()->address;
		});

		customer.recv([&](const Mail &mail) {
			REQUIRE(mail.hotelName == "marriott");
		});
	};
}

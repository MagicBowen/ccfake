#include "catch2/catch.hpp"
#include "hotel/customer.h"
#include "hotel/hotel.h"

CCFAKE_NS_USING;

std::string HOTEL_NAME;
std::string HOTEL_ADDR;

struct Mail {
	static const Mail* pop() {
		return nullptr;
	}

	static Status put(Mail& mail) {
		HOTEL_NAME = mail.hotelName;
		HOTEL_ADDR = mail.hotelAddress;
		return Status::SUCCESS;
	}

	std::string hotelName;
	std::string hotelAddress;
};

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

	Customer customer{"Bowen"};

	SECTION("send mail to hotel") {
		customer.submit([&](Mail &mail) {
			mail.hotelName = Dtree(Amber).get<Hotel>()->name;
			mail.hotelAddress = Dtree(Amber).get<Hotel>()->address;
		});

		REQUIRE(HOTEL_NAME == "Amber");
		REQUIRE(HOTEL_ADDR == "ShangHai");
	};
}

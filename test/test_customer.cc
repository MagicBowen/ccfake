#include "catch2/catch.hpp"
#include "ccfake/ccfake.h"
#include "hotel/customer.h"
#include "hotel/hotel.h"

CCFAKE_NS_USING;

std::string HOTEL_NAME;
std::string HOTEL_ADDR;

CCFAKE_MSG(Mail) {
	static MsgPtr fetch() {
		auto mail = new Mail;
		mail->hotelName = "marriott";
		return MsgPtr(mail);
	}

	static Status submit(MsgPtr mail) {
		HOTEL_NAME = mail->hotelName;
		HOTEL_ADDR = mail->hotelAddress;
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
		customer.send([&](Mail &mail) {
			mail.hotelName = Dtree(Amber).get<Hotel>()->name;
			mail.hotelAddress = Dtree(Amber).get<Hotel>()->address;
		});

		customer.recv([&](const Mail &mail) {
			REQUIRE(mail.hotelName == "marriott");
		});

		REQUIRE(HOTEL_NAME == "Amber");
		REQUIRE(HOTEL_ADDR == "ShangHai");
	};
}

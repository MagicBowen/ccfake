#include "catch2/catch.hpp"
#include "ccfake/ccfake.h"
#include "hotel/customer.h"
#include "hotel/hotel.h"

CCFAKE_NS_USING;

std::string HOTEL_NAME;
std::string HOTEL_ADDR;

TEST_CASE("Customer Test") {

	HOTEL(Marriott) {
		ATTR(address, "Xi'an");

		MAIL_BOX {
			ATTR(capacity, 1);
		};
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

	Customer customer{"Bowen", *Marriott};

	auto mailBox = Dtree(Marriott).get<MailBox>();

	REQUIRE(mailBox->getMailCount() == 0);

	SECTION("send and recv mails by customer") {
		customer.sendMail([&](Mail &mail) {
			mail.title = "Order";
			mail.address = Marriott->address;
		});

		REQUIRE(mailBox->getMailCount() == 1);

		customer.recvMail([&](const Mail &mail) {
			REQUIRE(mail.title == "Order");
			REQUIRE(mail.address == "Xi'an");
		});

		REQUIRE(mailBox->getMailCount() == 0);
	};
}

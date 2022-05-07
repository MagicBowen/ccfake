#include "catch2/catch.hpp"
#include "device/modem.h"
#include "ccfake/log/log.h"

CCFAKE_NS_USING;

SCENARIO("Sample Test") {

	DTREE_(Device, device) {
		NODE_(Modem, 0) {
			ATTR_(ratMode, "nr");
			LEAF_(Band, 1, "lte");
		};
		NODE_(RxProtect, 0) {
			ATTR_(name, "protect");
		};
	};


	auto protect = DTREE_FIND_NODE(device, RxProtect, self.id == 0);
//
    REQUIRE(protect != nullptr);
    REQUIRE(protect->name == "protect");

    auto band = DTREE_FIND_NODE(device, Band, self.id == 0);

	REQUIRE(band == nullptr);

	band = DTREE_FIND_NODE(device, Band, self.id == 1);

	REQUIRE(band != nullptr);
	REQUIRE(band->ratMode == "lte");

	auto modem = DTREE_FIND_ROOT(band, Modem);
	REQUIRE(modem != nullptr);
	REQUIRE(modem->id == 0);
	REQUIRE(modem->ratMode == "nr");
}

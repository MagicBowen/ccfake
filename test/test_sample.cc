#include "catch2/catch.hpp"
#include "device/modem.h"

CCFAKE_NS_USING;

SCENARIO("Sample Test") {

	DTREE_OF(Device, device) {
		DTREE_NODE_OF(Modem, 0) {
			self.ratMode = "nr";
			DTREE_LEAF_OF(Band, 1, "lte");
		};
		DTREE_NODE_OF(RxProtect, 0) {
			self.name = "protect";
		};
	};

	auto protect = device->getNodeBy<RxProtect>([](const auto& p) {
		return (p.id == 0);
	});

    REQUIRE(protect != nullptr);
    REQUIRE(protect->name == "protect");

	auto band = device->getNodeBy<Band>([](const auto& b) {
		return (b.id == 0);
	});

	REQUIRE(band == nullptr);

	band = device->getNodeBy<Band>([](const auto& b) {
		return (b.id == 1);
	});
	REQUIRE(band != nullptr);
	REQUIRE(band->ratMode == "lte");

	auto modem = band->getRootOf<Modem>();
	REQUIRE(modem != nullptr);
	REQUIRE(modem->id == 0);
	REQUIRE(modem->ratMode == "nr");
}

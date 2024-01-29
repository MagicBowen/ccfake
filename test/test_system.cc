#include "catch2/catch.hpp"
#include "hotel/hotel.h"
#include "hotel/hotel_layout.h"
#include "hotel/hotel_close.h"
#include "hotel/hotel_reserve.h"

CCFAKE_NS_USING;

CCFAKE_DTREE_NODE_TYPE(SystemNode) {
        DEFAULT(void, layout() const);
};

class Device : public SystemNode {
public:
    std::string name;
    std::string address{""};

public:
    Device(std::string name)
            : name{name} {
    }

private:
    OVERRIDE(void layout() const) {
        printf("Device : name(%s), address(%s)\n",
               name.c_str(), address.c_str());
    }
};

class Chip : public SystemNode {
public:
    std::size_t id;
    std::string type;

public:
    Chip(std::size_t id)
            : id{id} {
    }
};

class Port : public SystemNode {
public:
    std::size_t id;
    std::size_t band;

public:
    Port(std::size_t id)
            : id{id} {
    }
};

class Route : public SystemNode {
public:
}

CCFAKE_ACTOR_TYPE(Actor) {
    public:
    Actor(std::string name,  Device& device) {
    }

    template<typename CHECKER>
    void recv(const CHECKER& check) {
        Actor::fetch(check);
    }

    template<typename CHECKER>
    void send(const CHECKER& check) {
        Actor::submit(check);
    }

    private:
    Status fetchMsg(Mail& mail) {
        auto mailBox = Dtree(hotel).get<MailBox>();
        return mailBox->fetchMail(mail);
    }

    Status submitMsg(Mail& mail) {
        auto mailBox = Dtree(hotel).get<MailBox>();
        return mailBox->submitMail(mail);
    }

    friend struct Actor<Customer>;
};

#define DEVICE(NAME) 				CCFAKE_DTREE_OF(Device, NAME, #NAME)
#define CPU(ID)     				CCFAKE_DTREE_NODE_OF(Cpu, ID)
#define PORT(ID)     				CCFAKE_DTREE_NODE_OF(Port, ID)
#define ROUTE(...)

struct Event {
    int property;
};

struct Command {
    int type;
};

struct Request {
    int id;
};

struct Response {
    int id;
    bool status;
};

struct Ack {
    bool status;
};

SCENARIO("Flash Opening") {
    GIVEN("flashlight with enough power") {
        FlashLight(f) {
            Battery(0) {
                voltage(5_V)
                power(3_Ah)
            },
            Battery(1) {
                voltage(5_V)
                power(1_Ah)
            },
            Switch {
                status(OFF)
            },
            Lamp {
                rated_power(0.8_W)
            }
        };
        Actor usr{"Bob"};

        TEST_CASE("should light on when user opened it") {
            usr.open(f);
            REQUIRE(f.IsLightOn() == true);
        }
    }
}

SCENARIO("Device Usage") {
    GIVEN("system with two chips and linked by port 1 GB") {
        DEVICE(system) {
            CPU(0) {
                PORT(0) {
                    ATTR(band, 1_GB);
                };
                PORT(1) {
                    ATTR(band, 10_GB);
                };
            };
            CPU(1) {
                PORT(2) {
                    ATTR(band, 1_GB);
                };
            };
            ROUTE() {
                PORT(0) -> PORT(2);
            }
        };

        Actor actor1{"usr", system};
        Actor actor2{"dep_sys1", system};
        Actor actor3{"dep_sys2", system};

        TEST_CASE("dependent system reply OK") {
            actor1.send([](Event &event) {
                event.property = 1;
            });

            actor2.recv([](const Command &command) {
               REQUIRE(command.type == 0);
            });

            actor3.recv([](const Request &request) {
               REQUIRE(request.id == 0);
            });

            actor3.send([](Response &response) {
               response.status = true;
            });

            actor1.recv([](const Ack &ack) {
                REQUIRE(ack.status == true);
            });
        }
    }
}

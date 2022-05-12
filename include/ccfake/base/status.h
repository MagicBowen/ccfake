#ifndef CCFAKE_A25033D6_1564_4748_B2C8_4DE2C5A286DE
#define CCFAKE_A25033D6_1564_4748_B2C8_4DE2C5A286DE

#include "ccfake/base/ns.h"

CCFAKE_NS_BEGIN

enum class Status {
	SUCCESS = 0,
	DONE    = 1,

	RESERVED_FAIL = -1,
	FAILURE       = -2,
	FATAL_BUG     = -3,
	TIMEDOUT      = -4,
	OUT_OF_RANGE  = -5,
	UNIMPLEMENTED = -6,
};

static inline bool status_is_ok(Status status)
{
    return (status > Status::RESERVED_FAIL);
}

static inline bool status_is_failed(Status status)
{
    return !status_is_ok(status);
}

static inline bool status_is_done(Status status) {
	return status == Status::DONE;
}

static inline bool status_is_terminal(Status status) {
	return status_is_done(status) || status_is_failed(status);
}

CCFAKE_NS_END

#endif

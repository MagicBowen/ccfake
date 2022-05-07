#ifndef CCFAKE_369BC879F4AC489B816507B376F267E9
#define CCFAKE_369BC879F4AC489B816507B376F267E9

#include "ccfake/log/log_print.h"

CCFAKE_NS_BEGIN

#define CCFAKE_FATAL(fmt, ...) CCFAKE_LOG_PRINT(::CCFAKE_NS::LogLevel::FATAL, fmt, ##__VA_ARGS__)
#define CCFAKE_ERROR(fmt, ...) CCFAKE_LOG_PRINT(::CCFAKE_NS::LogLevel::ERROR, fmt, ##__VA_ARGS__)
#define CCFAKE_WARN(fmt, ...)  CCFAKE_LOG_PRINT(::CCFAKE_NS::LogLevel::WARN,  fmt, ##__VA_ARGS__)
#define CCFAKE_SUCC(fmt, ...)  CCFAKE_LOG_PRINT(::CCFAKE_NS::LogLevel::SUCC,  fmt, ##__VA_ARGS__)
#define CCFAKE_INFO(fmt, ...)  CCFAKE_LOG_PRINT(::CCFAKE_NS::LogLevel::INFO,  fmt, ##__VA_ARGS__)
#define CCFAKE_DEBUG(fmt, ...) CCFAKE_LOG_PRINT(::CCFAKE_NS::LogLevel::DEBUG, fmt, ##__VA_ARGS__)

CCFAKE_NS_END

#endif

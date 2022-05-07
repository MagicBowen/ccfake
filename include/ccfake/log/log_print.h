#ifndef CCFAKE_3CA6B30D5FB14F66B9783B7F7219185B
#define CCFAKE_3CA6B30D5FB14F66B9783B7F7219185B

#include "ccfake/log/log_file.h"
#include "ccfake/log/log_level.h"
#include <type_traits>
#include <exception>
#include <iostream>

CCFAKE_NS_BEGIN

namespace detail {
    template<typename T>
    auto printable_cast(T && t) -> decltype(auto) {
        if constexpr (std::is_same_v<std::string, std::decay_t<T>>) {
            return std::forward<T>(t).c_str();
        } else {
            return std::forward<T>(t);
        }
    }

    template<typename ... ARGS>
    std::string log_format(const std::string& format, ARGS && ... args){
        size_t size = 1 + snprintf(nullptr, 0, format.c_str(), printable_cast(args) ...);
        char bytes[size];
        snprintf(bytes, size, format.c_str(), printable_cast(args) ...);
        return std::string(bytes);
    }

    template<std::size_t Len, typename ... TS>
    void log_print(LogLevel level, const char(&file)[Len], unsigned int line, const char* fmt, TS && ...ts) {

        auto msg = std::string("[") + to_string(level) + "]: "
        		+ log_file_base_name(file) + ":" + std::to_string(line) + ": ";

        if constexpr (sizeof...(TS) > 0) {
            msg += log_format(fmt, std::forward<TS>(ts)...);
        }

        std::cout << color_fmt_of(level) << msg << color_fmt_of(LogLevel::NONE) << std::endl;

        if (level == LogLevel::FATAL) throw std::runtime_error(msg);
    }
}

/////////////////////////////////////////////////////////////////////
#define CCFAKE_LOG_PRINT(level, fmt, ...) 				                            \
do {													                            \
	if (::CCFAKE_NS::level_enabled(level)) {			                                \
		::CCFAKE_NS::detail::log_print(level,  __FILE__, __LINE__, fmt, ##__VA_ARGS__); \
	}										                                        \
} while(0)

CCFAKE_NS_END

#endif

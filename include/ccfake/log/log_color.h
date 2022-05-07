#ifndef CCFAKE_9271320288054727A41B4395384E898B
#define CCFAKE_9271320288054727A41B4395384E898B

#include "ccfake/base/ns.h"

CCFAKE_NS_BEGIN

enum class LogColor {
    RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,
};

constexpr const char* to_color_fmt(LogColor color) {
    switch (color) {
        case LogColor::RED     : return "\033[1;31m";
        case LogColor::GREEN   : return "\033[1;32m";
        case LogColor::YELLOW  : return "\033[1;33m";
        case LogColor::BLUE    : return "\033[1;34m";
        case LogColor::MAGENTA : return "\033[1;35m";
        case LogColor::CYAN    : return "\033[1;36m";
        case LogColor::WHITE   : return "\033[0m";
    }
    return "\033[0m";
}

CCFAKE_NS_END

#endif

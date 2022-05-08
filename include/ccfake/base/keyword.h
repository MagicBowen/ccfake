#ifndef HCAB11CC2_4568_4F52_8479_1C2CD7C05D8E
#define HCAB11CC2_4568_4F52_8479_1C2CD7C05D8E

#include "ccfake/base/default.h"

CCFAKE_NS_BEGIN

namespace details
{
   template<typename T>
   struct Interface
   {
      virtual ~Interface() = default;
   };
}

#define INTERFACE(Intf)  struct Intf : ::CCFAKE_NS::details::Interface<Intf>

#define ABSTRACT(...) virtual __VA_ARGS__ = 0

#define OVERRIDE(...) virtual __VA_ARGS__ override

#define EXTENDS(...) , ##__VA_ARGS__
#define IMPLEMENTS(...) EXTENDS(__VA_ARGS__)

CCFAKE_NS_END

#endif

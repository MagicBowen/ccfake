#ifndef H977AC5EA_7AC7_4066_9C13_945AC312EA9F
#define H977AC5EA_7AC7_4066_9C13_945AC312EA9F

#include "ccfake/base/ns.h"

CCFAKE_NS_BEGIN

namespace details
{
   template <typename T>
   struct DefaultValue
   {
      static T value()
      {
         return T();
      }
   };

   template <typename T>
   struct DefaultValue<T*>
   {
       static T* value()
       {
           return 0;
       }
   };

   template <typename T>
   struct DefaultValue<const T*>
   {
       static T* value()
       {
           return 0;
       }
   };

   template <>
   struct DefaultValue<void>
   {
      static void value()
      {
      }
   };
}

#define DEFAULT(type, method)  \
    virtual type method { return ::CCFAKE_NS::details::DefaultValue<type>::value(); }

CCFAKE_NS_END

#endif

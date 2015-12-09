#ifndef HX3D_CORE_PLATFORMS
#define HX3D_CORE_PLATFORMS

#ifdef __IPHONE_NA
  #define __IOS__
#elif __APPLE__
  #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
      #define __IOS_SIM__
    #elif TARGET_OS_IPHONE
      #define __IOS__
    #endif
#endif

#endif

#pragma once

#ifdef LINUX_PLATFORM
    #ifndef ASSERT
        #define ASSERT(expr)  (static_cast <bool> (expr) ? void (0) : __builtin_trap())
    #endif
#endif
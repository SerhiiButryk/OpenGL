#pragma once

#include <cassert>
#include <common/Log.h>

namespace test {

    void Assert(bool condition, const char* message) {
        if (!condition) {
           logError(message);
           assert(false);
        }
    }

}

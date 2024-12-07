#pragma once

#include <cassert>
#include <common/Log.h>

#define ASSERT(condition, message) \
    if (!condition) { \
        logError(message); \
        assert(false); \
    } \

#define ASSERT_TRUE(condition) \
    if (!condition) { \
    assert(false); \
    } \

namespace test {
}

#pragma once

#include <cassert>
#include <common/Log.h>

#define ASSERT_LOG(condition, message) \
    if (!(condition)) { \
        logError(message); \
        assert(false); \
    } \

#define ASSERT(condition) \
    if (!(condition)) { \
    assert(false); \
    } \

namespace test {
}

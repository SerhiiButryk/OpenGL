#pragma once

#include <cassert>
#include <common/Log.h>

#define ASSERT_LOG(condition, message) \
    if (!(condition)) { \
        LOG_ERROR(message); \
        assert(false); \
    } \

#define ASSERT(condition) \
    if (!(condition)) { \
    assert(false); \
    } \
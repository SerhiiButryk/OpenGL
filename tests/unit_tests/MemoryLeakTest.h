#pragma once

#include "base/Test.h"

namespace test {

    class MemoryLeakTest : public Test
    {
    public:
        int run() const override;
        const char* name() const override { return "MemoryLeakTest"; }
    };

}

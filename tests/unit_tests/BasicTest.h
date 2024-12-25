#pragma once

#include "base/Test.h"

namespace test {

    class BasicTest : public Test
    {
    public:
        int run() const override;
        const char* name() const override { return "BasicTest"; }
    };

}

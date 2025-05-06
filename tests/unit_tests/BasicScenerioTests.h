#pragma once

#include <base/Test.h>

namespace test {

    class BasicScenerioTests : public Test
    {
    public:
        int run() const override;
        const char* name() const override { return "BasicScenerioTests"; }
    };

}

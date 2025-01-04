#pragma once

#include "base/TestCase.h"

namespace test {

    class BackgroundColorTest : public TestCase
    {
    public:
        BackgroundColorTest() = default;
        ~BackgroundColorTest() override = default;

        void onCreate(Application* app) override;
        void onDestroy() override;
        void onRender() override;
    };

}

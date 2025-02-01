#pragma once

#include <base/TestCase.h>

namespace test {

    class ShapesTest : public TestCase
    {
    public:
        explicit ShapesTest(Application* app) : TestCase(app) {}

        void onCreate(Application* app) override;
        void onDestroy() override;
        void onRender() override;
    
    };

}

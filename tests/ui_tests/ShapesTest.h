#pragma once

#include <base/TestCase.h>

namespace test {

    class ShapesTest : public TestCase
    {
    public:
        void onCreate(Application* app) override;
        void onDestroy() override;
        void onRender() override;
    
    };

}

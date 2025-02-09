#pragma once

#include <base/TestCase.h>

namespace test {

    class ShapesTest : public TestCase
    {
    public:
        explicit ShapesTest(Application* app) : TestCase(app) {}

        void onAttach() override;

        void onDraw() override;

        void onDetach() override;
    
    };

}

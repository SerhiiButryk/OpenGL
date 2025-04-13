#pragma once

#include <base/TestCase.h>

namespace test {

    class BatchingTest : public TestCase
    {
    public:
        explicit BatchingTest(Application* app) : TestCase(app) {}

        void onAttach() override;

        void onDraw() override;

        void onDrawUI() override;

        void onDetach() override;
    };

}

#pragma once

#include <base/TestCase.h>

namespace test {

    class BatchingTest : public TestCase
    {
    public:
        explicit BatchingTest(Application* app) : TestCase(app) {}

        void onCreate(Application* app) override;
        void onDestroy() override;

        void onRender() override;
    };

}

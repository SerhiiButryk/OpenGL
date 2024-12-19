#pragma once

#include <base/TestCase.h>

namespace test {

    class DynamicBatching : public TestCase
    {
    public:
        void onCreate(Application* app) override;
        void onDestroy() override;
        void onBeforeRender() override;
        void onRender() override;
    };

}

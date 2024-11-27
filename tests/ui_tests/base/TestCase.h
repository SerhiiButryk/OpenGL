#pragma once

#include <Application.h>

namespace test {

    class TestCase
    {
    public:
        TestCase() = default;
        virtual ~TestCase() = default;

        virtual void onCreate(Application* app) {}
        virtual void onBeforeRender() {}
        virtual void onDestroy() {}
        virtual void onRender() {}
    };

}

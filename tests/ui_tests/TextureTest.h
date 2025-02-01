#pragma once

#include "base/TestCase.h"

namespace test {

    class TextureTest : public TestCase
    {
    public:
        explicit TextureTest(Application* app) : TestCase(app) {}
        ~TextureTest() override = default;

        void onCreate(Application* app) override;
        void onDestroy() override;

        void onRender() override;
    };

}

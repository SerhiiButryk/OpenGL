#pragma once

#include "base/TestCase.h"

namespace test {

    class TextureTest : public TestCase
    {
    public:
        TextureTest() = default;
        ~TextureTest() override = default;

        void onCreate(Application* app) override;
        void onDestroy() override;
        void onBeforeRender() override;
        void onRender() override;
    };

}

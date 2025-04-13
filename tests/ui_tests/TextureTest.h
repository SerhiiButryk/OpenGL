#pragma once

#include "base/TestCase.h"

namespace test {

    class TextureTest : public TestCase
    {
    public:
        explicit TextureTest(Application* app) : TestCase(app) {}
        ~TextureTest() override = default;

        void onAttach() override;

        void onDraw() override;

        void onDrawUI() override;

        void onDetach() override;
    };

}

#pragma once

#include "public/XEngine.h"

namespace test {

    /**
    *  Call and test OpenGL APIs here
    */

    class BlankTest : public xengine::UIComponent
    {
    public:

        void onAttach() override;

        void onDraw() override;

        void onDetach() override;
    };

}
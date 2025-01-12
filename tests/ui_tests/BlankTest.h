#pragma once

#include "public/XEngine.h"

namespace test {

    /**
    *  Call and test OpenGL APIs here
    */

    class BlankTest : public xengine::UI
    {
    public:

        void onCreate() override;

        void onDraw() override;

        void onDestroy() override;
    };

}
#pragma once

#include "base/TestUI.h"

namespace test {

    class BackgroundColorTest : public TestUI
    {
    public:
        BackgroundColorTest() = default;
        ~BackgroundColorTest() override = default;

        void onCreate() override;
        void onRender() override;
        void onDestroy() override;
        void onRenderUI() override;
    };

}

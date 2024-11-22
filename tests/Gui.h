#pragma once

#include "public/XEngine.h"

namespace client {

    class Gui : public xengine::UI {
    public:
        Gui() = default;
        virtual ~Gui() = default;

        void onCreateUI() override;
        void onRenderUI() override;
        void onDestroyUI() override;
    };

}

#pragma once

#include "public/XEngine.h"
#include <Application.h>

namespace client {

    class TestUI : public xengine::UI {
    public:
        explicit TestUI(Application* app) : m_app(app) {}
        ~TestUI() override = default;

        void onCreate() override;
        void onRender() override;
        void onDestroy() override;

    private:
        Application* m_app = nullptr;
    };

}

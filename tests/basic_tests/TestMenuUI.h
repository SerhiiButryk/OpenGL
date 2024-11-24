#pragma once

#include "public/XEngine.h"
#include "Application.h"

namespace client {

    class TestMenuUI : public xengine::UI {
    public:
        explicit TestMenuUI(Application* app) : m_app(app) {}
        ~TestMenuUI() override = default;

        void onCreate() override;
        void onRender() override;
        void onDestroy() override;

    private:
        Application* m_app = nullptr;
    };

}

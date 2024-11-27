#pragma once

#include <Application.h>
#include "public/XEngine.h"

namespace test {

    class TestUI : public xengine::UI
    {
    public:
        TestUI() = default;
        explicit TestUI(Application* app) : m_app(app) {}

        ~TestUI() override = default;

        void onCreate() override;
        void onRender() override;
        void onDestroy() override;

        // Should be called to create ImGui UI
        virtual void onRenderUI();

    protected:
        Application* m_app = nullptr;
    };

}
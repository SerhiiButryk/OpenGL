#pragma once

#include <Application.h>
#include <opengl/shapes/Color.h>

#include "public/XEngine.h"

namespace test {

    class TestUI : public xengine::UI
    {
    public:
        TestUI() = default;
        explicit TestUI(Application* app) : m_app(app) {}

        ~TestUI() override = default;

        void onCreate() override;
        void onDraw() override;
        void onDestroy() override;

        // Should be called to create ImGui UI
        virtual void onRenderUI();

    protected:
        Application* m_app = nullptr;
        // Nice grey color initially
        float m_color[4] = Color(xengine::GREY_COLOR);
    };

}
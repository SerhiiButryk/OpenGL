#pragma once

#include <Application.h>
#include <opengl/shapes/Color.h>

#include "public/XEngine.h"

namespace test {

    class TestUI : public xengine::UIComponent
    {
    public:
        TestUI() = default;
        explicit TestUI(Application* app) : m_app(app) {}

        ~TestUI() override = default;

        void onAttach() override;

        void onDetach() override;

        void onDraw() override;

        // Should be called to create ImGui UI
        virtual void onRenderUI() = 0;

    protected:
        Application* m_app = nullptr;
        // Nice grey color initially
        float m_color[4] = Color(xengine::GREY_COLOR);
    };

}
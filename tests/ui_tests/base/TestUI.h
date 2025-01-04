#pragma once

#include <Application.h>
#include <glm/vec4.hpp>

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

        void setColor(const glm::vec4& color) { m_color = color; }
        glm::vec4& getColor() { return m_color; }

    protected:
        Application* m_app = nullptr;
        // Nice grey color initially
        glm::vec4 m_color = { 192.0f / 255.0f, 194.0f / 255.0f, 201.0f / 255.0f, 1.0f };
    };

}
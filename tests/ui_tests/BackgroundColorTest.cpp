#include "BackgroundColorTest.h"

#include <base/TestUI.h>
#include <opengl/Renderer.h>
#include <imgui/imgui.h>

static xengine::Renderer* renderer = nullptr;

static const char* color_picker_label = "Current color";

namespace test {

    void BackgroundColorTest::onCreate(Application* app) {
        renderer = new xengine::Renderer();
    }

    void BackgroundColorTest::onDestroy() {
        delete renderer;
    }

    void BackgroundColorTest::onRender() {

        void* p = getTestUI();
        auto test_ui = static_cast<TestUI*>(p);

        glm::vec4 vecColor = test_ui->getColor();

        float color[] = { vecColor.x, vecColor.y, vecColor.z, vecColor.w };

        if (ImGui::ColorEdit3(color_picker_label, color)) {
            // Update color
            vecColor = { color[0], color[1], color[2], 1.0f };
            test_ui->setColor(vecColor);
        }
    }
}

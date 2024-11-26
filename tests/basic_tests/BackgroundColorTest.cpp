#include "BackgroundColorTest.h"

#include <opengl/Renderer.h>
#include <imgui/imgui.h>

static xengine::Renderer* renderer = nullptr;

// Nice grey color initially
static float color[] = { 192.0f / 255.0f, 194.0f / 255.0f, 201.0f / 255.0f };
static float alpha = 1.0f;

static const char* color_picker_label = "Current color";

namespace test {

    void BackgroundColorTest::onCreate() {
        renderer = new xengine::Renderer();
    }

    void BackgroundColorTest::onDestroy() {
        delete renderer;
    }

    void BackgroundColorTest::onRender() {
        // Clear screen to some initial starting color,
        // so we can draw things again from the begging
        renderer->clean(color[0], color[1], color[2], alpha);
    }

    void BackgroundColorTest::onRenderUI() {
        ImGui::ColorEdit3(color_picker_label, color);
    }
}

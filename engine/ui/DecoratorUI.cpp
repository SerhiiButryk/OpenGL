#include "DecoratorUI.h"

#include <imgui.h>
#include <common/Log.h>
#include <external/GUIHelper.h>
#include <opengl/GLEngine.h>
#include <opengl/render/Renderer.h>

#include "Widgets.h"

namespace xengine {

    DecoratorUI::DecoratorUI(void* window): m_nativeWindow(window) {
    }

    DecoratorUI::~DecoratorUI() {

    }

    void DecoratorUI::onAttach() {

        LOG_INFO("DecoratorUI::onAttach");

        if (!m_isAttached) {
            GUIHelper::init(m_nativeWindow);
            m_isAttached = true;

            versionInfo1.reset(GLEngine::getGLInfoAsString());
            versionInfo2.reset(GLEngine::getVendorInfoAsString());
            versionInfo3.reset(GLEngine::getRendererInfoAsString());
        } else {

            LOG_ERROR("DecoratorUI::onAttach layer already attached");

#ifndef UNIT_TESTS
            throw std::runtime_error("DecoratorUI::onAttach layer already attached");
#endif
        }
    }

    void DecoratorUI::onDetach() {

        LOG_INFO("DecoratorUI::onDetach");

        if (m_isAttached) {
            GUIHelper::destroy();
            m_isAttached = false;
        } else {

            LOG_ERROR("DecoratorUI::onDetach layer not attached");

#ifndef UNIT_TESTS
            throw std::runtime_error(std::string("DecoratorUI::onDetach layer not attached"));
#endif
        }
    }

    void DecoratorUI::onDrawUI() {
        drawDebugUI();
    }

    void DecoratorUI::onDraw() {
        // Clear screen as we are the first layer to render
        Renderer::clearScreen({m_color[0], m_color[1], m_color[2], m_color[3]});
    }

    void DecoratorUI::drawDebugUI() {

        static auto title = "Debug menu";
        static auto fps_label = "Performance: %.3f ms/frame (%.1f FPS)";
        static auto color_picker_label = "Set color";
        static auto debug_log_enable_label = "Enable debug logs";

        // Debug tab
        ImGui::Begin(title);

        // Debug info
        addText(fps_label, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        addText(versionInfo1.get());
        addText(versionInfo2.get());
        addText(versionInfo3.get());

        addColorPicker(color_picker_label, m_color, [](const char* text) {});

        if (addCheckBox(debug_log_enable_label, m_enableDebugLogs)) {
            Log::getInstance().setLogLevel(m_enableDebugLogs);
        }

        ImGui::End();
    }

}

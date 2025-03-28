#include "DecoratorUI.h"

#include <common/Log.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace xengine {

    DecoratorUI::DecoratorUI(void* window): m_nativeWindow(window) {
    }

    DecoratorUI::~DecoratorUI() {

    }

    void DecoratorUI::onAttach() {

        LOG_INFO("DecoratorUI::onAttach init decorator layer");

        if (!m_isAttached) {

            /////////////////////////////////////
            // A point of ImGui library initialization
            /////////////////////////////////////

            ImGui::CreateContext();

            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            // TODO: Docking doesn't work need to investigate
            // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.Fonts->AddFontDefault();
            io.FontGlobalScale = 1.3f;;

            ImGui::StyleColorsDark();

            auto window = static_cast<Window*>(m_nativeWindow);

            ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) window->getWindow(), true);

            const char* glsl_version = "#version 130";
            ImGui_ImplOpenGL3_Init(glsl_version);

            m_isAttached = true;
        } else {

            LOG_ERROR("DecoratorUI::onAttach layer already attached");

#ifndef UNIT_TESTS
            throw std::runtime_error("DecoratorUI::onAttach layer already attached");
#endif
        }
    }

    void DecoratorUI::onDetach() {

        LOG_INFO("DecoratorUI::onDetach release decorator layer");

        if (m_isAttached) {

            /////////////////////////////////////
            // Clear ImGui library resources
            /////////////////////////////////////

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            m_isAttached = false;
        } else {

            LOG_ERROR("DecoratorUI::onDetach layer not attached");

#ifndef UNIT_TESTS
            throw std::runtime_error(std::string("DecoratorUI::onDetach layer not attached"));
#endif
        }
    }

    void DecoratorUI::onDraw() {

    }

}

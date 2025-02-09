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

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.Fonts->AddFontDefault();
        io.FontGlobalScale = 1.3f;;

        ImGui::StyleColorsDark();

        auto window = static_cast<Window*>(m_nativeWindow);

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) window->getWindow(), true);

        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void DecoratorUI::onDetach() {
        LOG_INFO("DecoratorUI::onDetach release decorator layer");
        // Clear ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void DecoratorUI::onDraw() {

    }

}

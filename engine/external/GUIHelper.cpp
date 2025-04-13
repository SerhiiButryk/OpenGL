#include "GUIHelper.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <window/Window.h>

#include "GLFW/glfw3.h"

namespace xengine {

    void GUIHelper::init(void* w) {

        /////////////////////////////////////
        // A point of ImGui library initialization
        /////////////////////////////////////

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

        io.Fonts->AddFontDefault();
        io.FontGlobalScale = 1.3f;;

        ImGui::StyleColorsDark();

        auto window = static_cast<Window*>(w);

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) window->getWindow(), true);

        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void GUIHelper::destroy() {

        /////////////////////////////////////
        // Clear ImGui library resources
        /////////////////////////////////////

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void GUIHelper::beginGUI() {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void GUIHelper::endGUI() {
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

}

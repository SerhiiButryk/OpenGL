#include "TestUI.h"

#include <common/Log.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

static const char* title = "App menu";
static const char* fps_label = "Application average %.3f ms/frame (%.1f FPS)";

namespace test {

    void TestUI::onCreate() {
        LOG_INFO("TestUI::onCreate");

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.Fonts->AddFontDefault();
        io.FontGlobalScale = 1.3f;;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) m_app->getMainApplication()->getWindow(), true);

        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void TestUI::onRender() {

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin(title);

        ImGui::Text(fps_label, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Spacing();

        // Should be called to create ImGui UI
        onRenderUI();

        ImGui::End();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void TestUI::onDestroy() {
        LOG_INFO("TestUI::onDestroy");
        // Clear ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void TestUI::onRenderUI() {
    }
}

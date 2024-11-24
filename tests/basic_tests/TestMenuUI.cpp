#include "TestMenuUI.h"

#include <Application.h>
#include <common/Log.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <opengl/Renderer.h>

static xengine::Renderer* renderer = nullptr;

namespace client {

    void TestMenuUI::onCreate() {
        logInfo("TestMenuUI::onCreate");

        renderer = new xengine::Renderer();

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) m_app->getMainApplication()->getWindow(), true);

        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void TestMenuUI::onRender() {

        // Nice grey color
        float red = 192 / 255.0;
        float green = 194 / 255.0;
        float blue = 201 / 255.0;

        // Clear screen to some initial starting color,
        // so we can draw things again from the begging
        renderer->clean(red, green, blue, 1.0f);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Test application");

            ImGui::Button("Test button");

            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void TestMenuUI::onDestroy() {
        logInfo("TestMenuUI::onDestroy");
        // Clear ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        delete renderer;
    }

}

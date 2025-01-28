#include "TestUI.h"

#include <common/Log.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <opengl/GLEngine.h>

static const char* title = "Test menu";
static const char* title2 = "Settings menu";
static const char* fps_label = "Performance: %.3f ms/frame (%.1f FPS)";
static const char* version_info_label;

namespace test {

    void TestUI::onCreate() {
        LOG_INFO("TestUI::onCreate");

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.Fonts->AddFontDefault();
        io.FontGlobalScale = 1.3f;;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) m_app->getNativeWindow(), true);

        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);

        version_info_label = xengine::GLEngine::getVersionsInfo();
    }

    void TestUI::onDraw() {

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Tab 1
        ImGui::Begin(title);

        ImGui::Spacing();

        // Should be called to create ImGui UI
        onRenderUI();

        ImGui::End();

        // Tab 2
        ImGui::Begin(title2);

        ImGui::Text(fps_label, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Text(version_info_label);

        // TODO: Add a list selection
        // const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
        // static int item_selected_idx = 0; // Here we store our selected data as an index.
        //
        // static bool item_highlight = false;
        // int item_highlighted_idx = -1; // Here we store our highlighted data as an index.
        // // ImGui::Checkbox("Highlight hovered item in second listbox", &item_highlight);
        //
        // if (ImGui::BeginListBox("listbox 1"))
        // {
        //     for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        //     {
        //         const bool is_selected = (item_selected_idx == n);
        //         if (ImGui::Selectable(items[n], is_selected))
        //             item_selected_idx = n;
        //
        //         if (item_highlight && ImGui::IsItemHovered())
        //             item_highlighted_idx = n;
        //
        //         // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
        //         if (is_selected)
        //             ImGui::SetItemDefaultFocus();
        //     }
        //     ImGui::EndListBox();
        // }

        xengine::addColorPicker("Set color", m_color, [](const char* text) {});

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

        free((char*) version_info_label);
    }

    void TestUI::onRenderUI() {
    }
}

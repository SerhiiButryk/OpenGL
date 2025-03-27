#include "TestUI.h"

#include <common/Log.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <opengl/GLEngine.h>

#include <memory>

static const char* title = "Test menu";
static const char* title2 = "Debug menu";
static const char* fps_label = "Performance: %.3f ms/frame (%.1f FPS)";

static std::unique_ptr<char> versionInfo1;
static std::unique_ptr<char> versionInfo2;
static std::unique_ptr<char> versionInfo3;

namespace test {

    void TestUI::onAttach() {
        // get.. fun creates a duplicated string that's why we need to delete it
        // smart pointer will do this
        versionInfo1.reset(xengine::GLEngine::getGLInfoAsString());
        versionInfo2.reset(xengine::GLEngine::getVendorInfoAsString());
        versionInfo3.reset(xengine::GLEngine::getRendererInfoAsString());
    }

    void TestUI::onDetach() {
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

        // Debug info
        xengine::addText(fps_label, 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        xengine::addText(versionInfo1.get());
        xengine::addText(versionInfo2.get());
        xengine::addText(versionInfo3.get());

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

}

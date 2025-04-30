#pragma once

#include <imgui.h>

namespace xengine {

    void addSpace();

    template <typename Callable>
    void addButton(const char* text, Callable &&callable, bool placeInRaw = true) {

        // For safety can add static check if template type is callable

        if (placeInRaw) {
            ImGui::SameLine();
        }
        if (ImGui::Button(text)) {
            callable(text);
        }
    }

    void addInputField(const char* text, void* value, void (*onClick)(const char* text));

    template <typename Callable>
    void addColorPicker(const char* text, float* value, Callable &&callable) {
        addSpace();
        if (ImGui::ColorEdit3(text, value)) {
            callable(text);
        }
        addSpace();
    }

    void addText(const char* fmt, ...);

    bool addCheckBox(const char* label, bool& v);

}
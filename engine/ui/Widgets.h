#pragma once

#include <imgui.h>

namespace xengine {

    void addSpace();
    void setSameLine();

    template<typename Callable>
    void addButton(const char *text, Callable &&callable, bool placeInRaw = true) {
        // For safety can add static check if template type is callable

        if (placeInRaw) {
            ImGui::SameLine();
        }
        if (ImGui::Button(text)) {
            callable(text);
        }
    }

    template<typename Callable>
    void addColorPicker(const char *text, float *value, Callable &&callable) {
        addSpace();
        if (ImGui::ColorEdit3(text, value)) {
            callable(text);
        }
        addSpace();
    }

    void addText(const char *fmt, ...);

    bool addCheckBox(const char *label, bool &v, bool sameLine = false);

    template<typename Callable>
    void addInputField(const char *text, const char *id, void *value, Callable &&callable, bool sameLine = false,
                       float fieldWidth = -1.0f) {

        if (sameLine) {
            ImGui::SameLine();
        }

        ImGui::Text(text);
        ImGui::SameLine();

        // Set custom id in the following format: 'text###id'
        const char* idPlaceholder = "###";

        size_t s2 = strlen(id);
        // 3 for "###" string and 1 for '\0'
        char label[s2 + 3 + 1] = {};

        strcat(label, idPlaceholder);
        strcat(label, id);

        if (fieldWidth > 0.0f) {
            ImGui::PushItemWidth(fieldWidth);
        }

        if (ImGui::InputFloat(label, (float *) value)) {
            callable(id);
        }

        if (fieldWidth > 0.0f) {
            ImGui::PopItemWidth();
        }
    }

}

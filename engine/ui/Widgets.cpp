#include "Widgets.h"

#include <imgui.h>

namespace xengine {

    void addButton(const char* text, void (*onClick)(const char* text), bool placeInRaw) {
        if (placeInRaw) {
            ImGui::SameLine();
        }
        if (ImGui::Button(text)) {
            onClick(text);
        }
    }

    void addInputField(const char* text, void* value, void (*onClick)(const char* text)) {

        addSpace();

        if (ImGui::InputFloat(text, (float*) value)) {
            onClick(text);
        }
    }

    void addSpace() {
        ImGui::Spacing();
    }

    void addColorPicker(const char* text, float* value, void (*onClick)(const char* text)) {
        addSpace();
        if (ImGui::ColorEdit3(text, value)) {
            onClick(text);
        }
        addSpace();
    }

    void addText(const char* fmt, ...) {
        addSpace();
        va_list args;
        va_start(args, fmt);
        ImGui::TextV(fmt, args);
        va_end(args);
    }

}

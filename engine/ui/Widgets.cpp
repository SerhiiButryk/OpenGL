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

}

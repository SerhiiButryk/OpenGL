#include "Widgets.h"

#include <common/Log.h>

namespace xengine {

    void addInputField(const char* text, void* value, void (*onClick)(const char* text)) {

        addSpace();

        if (ImGui::InputFloat(text, (float*) value)) {
            onClick(text);
        }
    }

    void addSpace() {
        ImGui::Spacing();
    }

    void addText(const char* fmt, ...) {
        addSpace();
        va_list args;
        va_start(args, fmt);
        ImGui::TextV(fmt, args);
        va_end(args);
    }

    bool addCheckBox(const char* label, bool& v) {
        addSpace();
        return ImGui::Checkbox(label, &v);
    }

}

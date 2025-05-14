#include "Widgets.h"

#include <common/Log.h>

namespace xengine {

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

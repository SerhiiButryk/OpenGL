#pragma once

namespace xengine {

    void addButton(const char* text, void (*onClick)(const char* text), bool placeInRaw = true);

    void addInputField(const char* text, void* value, void (*onClick)(const char* text));

    void addColorPicker(const char* text, float* value, void (*onClick)(const char* text));

    void addSpace();

    void addText(const char* fmt, ...);

}
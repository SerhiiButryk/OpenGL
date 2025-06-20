#pragma once

namespace xengine {

    [[maybe_unused]] static inline float GREY_COLOR[] = { 192.0f / 255.0f, 194.0f / 255.0f, 201.0f / 255.0f, 1.0f };
    [[maybe_unused]] static inline float GREY_COLOR_DARK[] = { 93.0f / 255.0f, 93.0f / 255.0f, 93.0f / 255.0f, 1.0f };
    [[maybe_unused]] static inline float GREY_COLOR_LIGHT[] = { 72.0f / 255.0f, 72.0f / 255.0f, 72.0f / 255.0f, 1.0f };
    [[maybe_unused]] static inline float BLACK_COLOR[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    #define Color(color) { color[0], color[1], color[2], color[3] }

};

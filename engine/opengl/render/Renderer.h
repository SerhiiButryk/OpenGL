#pragma once

#include "glm/vec4.hpp"
#include "opengl/render/RendererAPI.h"

namespace xengine {

    /**
     * High level renderer layer
     */
    class Renderer : public RendererAPI
    {
    public:

        static void clearScreen(glm::vec4 color);

        void drawRectangle(const glm::mat4& tansform = glm::mat4(1.0f)) override;

        void drawLine(const glm::mat4& tansform = glm::mat4(1.0f)) override;

    private:
        void setCommonConfigs(const glm::mat4& tansform);
    };
}

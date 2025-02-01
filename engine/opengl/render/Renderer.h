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

        void drawRectangle() override;

        void drawLine() override;

    private:
        void setCommonConfigs();
    };
}

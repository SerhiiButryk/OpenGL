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

        void drawRectangle(const RenderData::Objects& object) override;

        void drawLine(const RenderData::Objects& object) override;

    private:
        void setCommonConfigs(const RenderData::Objects& object);
    };
}

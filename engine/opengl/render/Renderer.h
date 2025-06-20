#pragma once

#include "opengl/render/RendererAPI.h"

namespace xengine {

    /**
     * High level renderer layer
     */
    class Renderer : public RendererAPI
    {
    public:

        static void clearScreen(glm::vec4 color);

        void drawRectangle(const Object* object) override;

    private:
        void setCommonConfigs(const Object* object);
    };
}

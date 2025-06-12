#pragma once

#include <opengl/render/RenderData.h>

namespace xengine {

    /**
     * High level renderer abstraction
     */
    class RendererAPI
    {
    public:
        RendererAPI() = default;
        virtual ~RendererAPI() = default;

        virtual void drawRectangle(const Object* object) = 0;

        virtual void drawLine(const Object* object) = 0;

    };

}

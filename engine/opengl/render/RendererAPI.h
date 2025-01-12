#pragma once

#include <opengl/render/RenderData.h>

namespace xengine {

    /**
     * High level renderer abstract API
     */
    class RendererAPI
    {
    public:
        RendererAPI() = default;
        virtual ~RendererAPI() = default;

        virtual void drawRectangle() const = 0;

        virtual void drawLine() const = 0;

        auto* getData() const { return m_renderData; }
        void setData(RenderData* command) { m_renderData = command; }

    protected:
          RenderData* m_renderData = nullptr;

    };

}

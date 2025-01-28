#pragma once

#include <opengl/render/RenderData.h>

namespace xengine {

    /**
     * High level abstract renderer APIs
     */
    class RendererAPI
    {
    public:
        RendererAPI() = default;
        virtual ~RendererAPI() = default;

        virtual void drawRectangle() = 0;

        virtual void drawLine() = 0;

        auto* getData() const { return m_renderData; }
        void setData(RenderData* command) { m_renderData = command; }

    protected:
          RenderData* m_renderData = nullptr;

    };

}

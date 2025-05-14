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

        virtual void drawRectangle(const RenderData::Objects& object) = 0;

        virtual void drawLine(const RenderData::Objects& object) = 0;

        auto* getData() const { return m_renderData; }
        void setData(RenderData* data) { m_renderData = data; }

    protected:
          RenderData* m_renderData = nullptr;

    };

}

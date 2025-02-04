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

        virtual void drawRectangle(const glm::mat4& tansform = glm::mat4(1.0f)) = 0;

        virtual void drawLine(const glm::mat4& tansform = glm::mat4(1.0f)) = 0;

        auto* getData() const { return m_renderData; }
        void setData(RenderData* command) { m_renderData = command; }

    protected:
          RenderData* m_renderData = nullptr;

    };

}

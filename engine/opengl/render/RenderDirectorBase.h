#pragma once

#include <opengl/render/RenderData.h>
#include "RendererAPI.h"

namespace xengine {

    /**
     * Class which manages some sort of Graphics pipline setup in OpenGL pipeline
     *
     * This is where we prepare all things for rendering and call render APIs
     *
     */
    class RenderDirectorBase {
    public:
        RenderDirectorBase();
        virtual ~RenderDirectorBase() = default;

        void createVertexBuffer(unsigned int size = 0);

        // Pipline settings START

        void begin(RenderData* data);

        void setShader(const std::string& filePath);
        void setTexture(const std::string& filePath, const std::string& textureName);

        void end();

        // Pipline settings END

        void batch(Shape &shape);

        virtual void render() = 0;

        virtual void submit(Shape& shape) = 0;
        virtual void submit(Vertex& vertex) = 0;

        void resetPointer() {
            m_renderData->configs.pointerStart = m_renderData->configs.drawBuffer;
            m_renderData->configs.vertexCount = 0;
        }

        // Getters

        void setData(RenderData *data) {
            this->m_renderData = data;
        }

    protected:
        RenderData* m_renderData {};
        RendererAPI* m_renderer {};

    private:
        void setIndexBuffer(IndexBuffer* ib, uint32_t maxSize) const;
    };

}

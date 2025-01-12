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

        void begin();

        void prepareShader(const std::string& filePath);
        void prepareTexture(const std::string& filePath, const std::string& textureName);
        void prepareMVPMatrix(const std::string& name);
        void prepareIndexBuffer(IndexBuffer* ib, uint32_t maxSize) const;

        void end();

        // Pipline settings END

        void batch(Shape &shape);

        virtual void render() = 0;

        virtual void addShape(Shape& shape) = 0;

        // Getters

        void setData(RenderData *data) {
            this->m_renderData = data;
        }

    protected:
        RenderData* m_renderData {};
        RendererAPI* m_renderer {};
    };

}

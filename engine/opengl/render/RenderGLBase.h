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
    class RenderGLBase {
    public:
        RenderGLBase();
        virtual ~RenderGLBase() = default;

        // Pipline APIs ////////////////////

        void begin(RenderData* data);

        void setShader(const std::string& filePath);
        void setTexture(const std::string& filePath, const std::string& textureName);

        virtual void submit(Shape* shape) = 0;

        void end();

        /////////////////////////////////////

        virtual void render() = 0;

        void setData(RenderData *data) {
            this->m_renderData = data;
        }

        bool hasRenderData() const {
            return m_renderData != nullptr;
        }

        void updateCamera(glm::vec3 position, float rotation) {
            m_renderData->camera->setPosition(position);
            m_renderData->camera->setRotation(rotation);
        }

        Camera* getCamera() {
            return m_renderData->camera;
        }

    protected:
        /**
         * NOTE: Class doesn't own render data object
         * lifecycle should be managed by upper layers
         */
        RenderData* m_renderData = nullptr;

        // TODO: Hardcoded might be dynamically configured
        RendererAPI* m_renderer = nullptr;

        void batch(Shape *shape);

        void createVertexBuffer(unsigned int size = 0);

    private:
        void setIndexBuffer(IndexBuffer* ib, uint32_t maxSize) const;
    };

}

#pragma once

#include <common/Log.h>
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

        void setConfigs(RenderData* data);
        void setPipeline(RenderData::Objects*);

        virtual void submit(RenderData::Objects* object) = 0;

        /////////////////////////////////////

        virtual void render() = 0;

        void setData(RenderData *data) {
            this->m_renderData = data;
        }

        RenderData* getData() {
            return m_renderData;
        }

        bool hasRenderData() const {
            return m_renderData != nullptr;
        }

        void releaseObjects();
        void releaseDrawBuffer();
        void releaseConfigs();

        Shape* getShapeById(unsigned int id);
        bool hasShapeById(unsigned int id);

    protected:
        /**
         * NOTE: Class doesn't own render data object
         * lifecycle should be managed by upper layers
         */
        RenderData* m_renderData = nullptr;

        // TODO: Hardcoded might be dynamically configured
        RendererAPI* m_impl = nullptr;

        // Track a list of objects which we render
        // Objects are owned by this class.
        std::vector<RenderData::Objects*> m_objectsList;

        RenderData::Objects* m_currentObject = nullptr;

        void batch(Shape *shape);
        void createVertexBuffer(unsigned int size = 0);

    private:

        void fillIndexBufferWithData(IndexBuffer* ib, uint32_t maxSize) const;

    };

}

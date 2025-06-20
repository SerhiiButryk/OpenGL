#pragma once

#include <opengl/render/RenderData.h>
#include "RendererAPI.h"

namespace xengine {

    /**
     * Class which manages Graphics pipline for OpenGL
     */

    class RenderGLBase {
    public:
        RenderGLBase();
        virtual ~RenderGLBase() = default;

        virtual void submit(Object* object) = 0;

        virtual void render() = 0;

        void releaseObjects();

        Shape* getShapeById(unsigned int id);
        bool hasShapeById(unsigned int id);

    protected:

        // TODO: Hardcoded might be dynamically configured
        RendererAPI* m_impl = nullptr;

        // Track a list of objects which we render
        // Objects are owned by this class.
        std::vector<Object*> m_objectsList;

        void batch(Object* objectSrc, Object* objectDst);
        void createDrawBuffer(Object* object, unsigned int size = 0);
        void createGLBuffers(Object*, size_t indexBuffSize = 0);

    };

}

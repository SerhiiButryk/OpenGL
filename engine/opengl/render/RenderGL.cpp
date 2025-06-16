#include "RenderGL.h"

#include <common/Log.h>
#include <opengl/shapes/Line.h>

namespace xengine {

    RenderGL::~RenderGL() {
        releaseObjects();
    }

    void RenderGL::render() {

        // Process the object list

        for (auto && object : m_objectsList) {

            LOG_DEBUG("RenderGL::render() rendering obj = '{:p}'", fmt::ptr(object));

            // Update buffer if shape is invalid
            if (object->shape->isInvalid()) {

                // Release draw buffer as we will override it
                // TODO: Duplicated code
                if (object->drawBuffer) {

                    delete [] (float*) object->drawBuffer;

                    object->drawBuffer = nullptr;
                    object->drawBufferPointer = nullptr;
                }

                object->elementCount = 0; // Also reset

                // TODO: Duplicated code
                // Create a buffer if it is not created
                createDrawBuffer(object);

                // Batch this shape into draw buffer
                batch(object);

                // Call to create VAO, VBO ets... for this object
                createGLBuffers(object);

                object->shape->reset();
            }

            m_impl->drawRectangle(object);
        }

    }

    void RenderGL::submit(Object* object) {

        // Create a buffer if it is not created
        createDrawBuffer(object);

        // Batch this shape into draw buffer
        batch(object);

        // Call to create VAO, VBO ets... for this object
        createGLBuffers(object);

        m_objectsList.push_back(object);

        LOG_DEBUG("RenderGL::submit() done, vertex count = '{}', new obj = '{:p}', total objects = '{}'",
            object->elementCount, fmt::ptr(object), m_objectsList.size());

    }

}

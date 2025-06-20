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

            LOG_DEBUG("RenderGL::render() rendering obj = '{:p}', total size = '{}'", fmt::ptr(object), m_objectsList.size());

            // Update buffer if shape is invalid
            if (object->getShape() && object->getShape()->isInvalid()) {

                // Reset buffer
                for (int i = 0; i < object->drawBufferSize; i++) {
                    Vertex::reset(&object->drawBuffer[i]);
                }

                object->elementIndex = 0;
                object->elementCount = 0; // Also reset

                // Update draw buffer
                batch(object, object);

                object->getShape()->reset();
            }

            m_impl->drawRectangle(object);
        }

    }

    void RenderGL::submit(Object* object) {

        if (m_isBatchStarted) {
            throw std::runtime_error("RenderGL::submit() called on a non-batch object");
        }

        // Create a buffer if it is not created
        createDrawBuffer(object);

        // Batch this shape into draw buffer
        batch(object, object);

        // Call to create VAO, VBO ets... for this object
        createGLBuffers(object);

        m_objectsList.push_back(object);

        LOG_DEBUG("RenderGL::submit() done, vertex count = '{}', new obj = '{:p}', total objects = '{}'",
            object->elementCount, fmt::ptr(object), m_objectsList.size());

    }

    void RenderGL::batchStart() {

        m_groupObject = new Object();

        m_isBatchStarted = true;
    }

    void RenderGL::batchSubmit(Object* object) {

        // Create a buffer if it is not created
        createDrawBuffer(m_groupObject, DEFAULT_VERTEX_BUFF_SIZE);

        // Batch this shape into draw buffer
        batch(object, m_groupObject);

        // Called once if buffers are not set
        if (m_groupObject->vertexArray == nullptr) {
            createGLBuffers(m_groupObject, DEFAULT_INDEX_BUFF_SIZE);
        }

        // Copy material
        m_groupObject->shader = object->shader;
        m_groupObject->texture = object->texture;

    }

    void RenderGL::batchEnd() {

        m_objectsList.push_back(m_groupObject);

        LOG_DEBUG("RenderGL::batchEnd() done, vertex count = '{}', new obj = '{:p}', total objects = '{}'",
            m_groupObject->elementCount, fmt::ptr(m_groupObject), m_objectsList.size());

        m_groupObject = nullptr;
        m_isBatchStarted = false;
    }

}

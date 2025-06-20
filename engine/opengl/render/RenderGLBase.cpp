#include "RenderGLBase.h"

#include <common/Log.h>
#include <opengl/render/Renderer.h>

#include <algorithm>

namespace xengine {

    RenderGLBase::RenderGLBase() {
        static Renderer renderer;
        m_impl = &renderer;
    }

    void RenderGLBase::batch(Object* objectSrc, Object* objectDst) {

        Vertex* destPointer = objectDst->drawBuffer + objectDst->elementIndex;
        Vertex* srcPointer = objectSrc->getShape()->getBuffer();

        // Batch object buffer
        for (int i = 0; i < objectSrc->getShape()->getVertexCount(); i++) {
            destPointer->position = srcPointer->position;
            destPointer->color = srcPointer->color;
            destPointer->texCoord = srcPointer->texCoord;
            destPointer->texIndex = srcPointer->texIndex;

            destPointer++;
            srcPointer++;
        }

        objectDst->elementIndex += objectSrc->getShape()->getVertexCount();
        objectDst->elementCount += objectSrc->getShape()->getElementCount();

        // Save to the list if objectDst != objectSrc
        // This is the case when we batch several objects into one
        if (objectDst != objectSrc) {
            objectDst->shape = objectSrc->getShape();
        }
    }

    void RenderGLBase::createDrawBuffer(Object* object, unsigned int size) {

        if (object->drawBuffer == nullptr) {

            if (size == 0) {
                size = object->getShape()->getVertexCount();
            }

            object->drawBufferSize = size;

            object->drawBuffer = new Vertex[object->drawBufferSize]{};
            object->elementIndex = 0;

            LOG_DEBUG("RenderGLBase::createVertexBuffer() created a buffer with size = {}", size);
        }

    }

    void RenderGLBase::createGLBuffers(Object* object, size_t indexBuffSize) {

        // VAO store the next calls
        // VertexBuffer.bind()
        // VertexBuffer.unbind()
        // IndexBuffer.bind()
        // IndexBuffer.unbind()
        // And attrib pointer data

        object->vertexArray = new VertexArray();
        object->vertexBuffer = new VertexBuffer();

        object->vertexArray->bind();
        object->vertexBuffer->bind();

        object->vertexBuffer->fill(nullptr, VERTEX_BYTES_SIZE(object->drawBufferSize), true);

        /*
            Bind vertex buffer and set attrib pointer for ABO
        */

        BufferLayout layout = Vertex::getLayout();
        object->vertexArray->add(*object->vertexBuffer, layout);

        object->indexBuffer = new IndexBuffer();
        object->indexBuffer->bind();

        size_t maxSize = (indexBuffSize == 0) ? object->elementCount : indexBuffSize;

        LOG_INFO("RenderGLBase::createGLBuffers() creating a buffer with size = {}", maxSize);

        uint32_t indices[maxSize] = {};

        object->shape->setIndicies(indices, maxSize);

        object->indexBuffer->fill(indices, maxSize);

    }

    void RenderGLBase::releaseObjects() {

        LOG_INFO("RenderGLBase::releaseObjects()");

        for (auto && obj : m_objectsList) {
            obj->free();
            delete obj;
        }

        m_objectsList.clear();
    }

    Shape* RenderGLBase::getShapeById(unsigned int id) {
        for (auto && obj : m_objectsList) {
            if (obj->shape->getID() == id) {
                return obj->shape;
            }
        }
        return nullptr;
    }

    bool RenderGLBase::hasShapeById(unsigned int id) {
        return getShapeById(id) != nullptr;
    }

}

#include "RenderGLBase.h"

#include <common/Log.h>
#include <opengl/render/Renderer.h>
#include <opengl/shapes/Rectangle.h>
#include <opengl/shapes/Triangle.h>

#include <algorithm>

namespace xengine {

    RenderGLBase::RenderGLBase() {
        static Renderer renderer;
        m_impl = &renderer;
    }

    void RenderGLBase::batch(Object* object) {

        auto* srcPointer = object->shape->getBuffer();
        auto* destPointer = (Vertex*) object->drawBufferPointer;

        for (int i = 0; i < object->shape->getVertexCount(); i++) {
            destPointer->position = srcPointer->position;
            destPointer->color = srcPointer->color;
            destPointer->texCoord = srcPointer->texCoord;
            destPointer->texIndex = srcPointer->texIndex;

            destPointer++;
            srcPointer++;
        }

        object->elementCount += object->shape->getElementCount();
    }

    void RenderGLBase::createDrawBuffer(Object* object, unsigned int size) {

        if (object->drawBuffer == nullptr) {

            size = object->shape->getVertexCount();

            object->drawBuffer = new Vertex[size]{};
            object->drawBufferPointer = object->drawBuffer;

            LOG_DEBUG("RenderGLBase::createVertexBuffer() created a buffer with size = {}", size);
        }

    }

    void RenderGLBase::createGLBuffers(Object* object) {

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

        object->vertexBuffer->createAndInitialize(nullptr, VERTEX_TOTAL_SIZE(object->elementCount), true);

        /*
            Bind vertex buffer and set attrib pointer for ABO
        */

        BufferLayout layout = Vertex::getLayout();
        object->vertexArray->add(*object->vertexBuffer, layout);

        object->indexBuffer = new IndexBuffer();
        object->indexBuffer->bind();

        fillIndexBufferWithData(object);

    }

    void RenderGLBase::fillIndexBufferWithData(Object* object) const {

        size_t maxSize = object->elementCount;

        LOG_INFO("RenderGLBase::fillIndexBufferWithData() creating a buffer with size = {}", maxSize);

        uint32_t indices[maxSize] = {};
        uint32_t offset = 0;

        // Set index buffer for rectangle

        auto rectangle = dynamic_cast<Rectangle*>(object->shape);

        if (rectangle) {
            // '6' represents 2 triangles with 3 * 2 vertices
            for (int i = 0; i < maxSize; i += 6 /* Makes up a single quad */) {

                indices[i + 0] = 0 + offset;
                indices[i + 1] = 1 + offset;
                indices[i + 2] = 2 + offset;

                indices[i + 3] = 2 + offset;
                indices[i + 4] = 3 + offset;
                indices[i + 5] = 0 + offset;

                offset += 4;
            }
        }

        // Set index buffer for triangle

        auto triangle = dynamic_cast<Triangle*>(object->shape);

        if (triangle) {
            indices[0] = 0;
            indices[1] = 1;
            indices[2] = 2;
        }

        object->indexBuffer->fill(indices, maxSize);
    }

    void RenderGLBase::releaseObjects() {

        LOG_INFO("RenderGLBase::releaseObjects()");

        for (auto && obj : m_objectsList) {

            if (obj->vertexArray) {
                obj->vertexArray->unbind();
            }

            if (obj->shader) {
                obj->shader->unBind();
            }

            if (obj->indexBuffer) {
                obj->indexBuffer->unbind();
            }

            if (obj->vertexBuffer) {
                obj->vertexBuffer->unbind();
            }

            if (obj->drawBuffer) {

                delete [] (float*) obj->drawBuffer;

                obj->drawBuffer = nullptr;
                obj->drawBufferPointer = nullptr;
            }

            delete obj->vertexArray;
            delete obj->vertexBuffer;
            delete obj->indexBuffer;
            delete obj->shader;
            delete obj->texture;
            delete obj->shape;

            delete obj;
        }

        m_objectsList.clear();
    }

    Shape* RenderGLBase::getShapeById(unsigned int id) {

        auto it = std::find_if (m_objectsList.begin(), m_objectsList.end(), [id](Object* obj) {
            return obj->shape->getID() == id;
        });

        return it == m_objectsList.end() ? nullptr : (*it)->shape;
    }

    bool RenderGLBase::hasShapeById(unsigned int id) {
        return getShapeById(id) != nullptr;
    }

}

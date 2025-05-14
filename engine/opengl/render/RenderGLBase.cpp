#include "RenderGLBase.h"

#include <common/Log.h>
#include <opengl/render/Renderer.h>
#include <algorithm>

namespace xengine {

    RenderGLBase::RenderGLBase() {
        // TODO: Might not be a good approach but it's a simple way !
        static Renderer renderer;
        m_impl = &renderer;
    }

    void RenderGLBase::batch(Shape* shape) {

        auto* srcPointer = shape->getBuffer();
        auto* destPointer = (Vertex*) m_renderData->configs.nextElementPointer;

        for (int i = 0; i < shape->getVertexCount(); i++) {
            destPointer->position = srcPointer->position;
            destPointer->color = srcPointer->color;
            destPointer->texCoord = srcPointer->texCoord;
            destPointer->texIndex = srcPointer->texIndex;

            destPointer++;
            srcPointer++;
        }

        m_renderData->configs.nextElementPointer = destPointer;
    }

    void RenderGLBase::createVertexBuffer(unsigned int size) {

        if (m_renderData->configs.drawBuffer == nullptr) {

            if (size == 0) {
                size = RenderData::DEFAULT_VERTEX_BUFF_SIZE;
            }

            LOG_INFO("RenderCommand::createVertexBuffer() creating a buffer with size = {}", size);

            m_renderData->configs.drawBuffer = new Vertex[size]{};
            m_renderData->configs.nextElementPointer = m_renderData->configs.drawBuffer;

        }

    }

    void RenderGLBase::setConfigs(RenderData* data) {
        setData(data);
    }

    void RenderGLBase::setPipeline(RenderData::Objects* object) {

        // VAO store calls
        // VertexBuffer.bind()
        // VertexBuffer.unbind()
        // IndexBuffer.bind()
        // IndexBuffer.unbind()
        // And attrib pointer data

        object->vertexArray = new VertexArray();
        object->vertexBuffer = new VertexBuffer();

        object->vertexArray->bind();
        object->vertexBuffer->bind();

        object->vertexBuffer->createAndInitialize(nullptr, VERTEX_TOTAL_SIZE(m_renderData->configs.vertexCount), true);

        /*
            Bind vertex buffer and set attrib pointer for ABO
        */

        BufferLayout layout = Vertex::getLayout();
        object->vertexArray->add(*object->vertexBuffer, layout);

        object->indexBuffer = new IndexBuffer();

        object->indexBuffer->bind();

        fillIndexBufferWithData(object->indexBuffer, m_renderData->configs.indexBufferMaxSize);

    }

    void RenderGLBase::fillIndexBufferWithData(IndexBuffer *ib, uint32_t maxSize) const {

        if (maxSize == 0) {
            maxSize = RenderData::DEFAULT_INDEX_BUFF_SIZE;
        }

        LOG_INFO("RenderCommand::fillIndexBufferWithData() creating a buffer with size = {}", maxSize);

        uint32_t indices[maxSize] = {};
        uint32_t offset = 0;

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

        ib->fill(indices, maxSize);
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

    void RenderGLBase::releaseDrawBuffer() {

        LOG_INFO("RenderGLBase::releaseDrawBuffer() m_renderData = '{:p}'", fmt::ptr(m_renderData));

        if (m_renderData) {

            delete [] (float*) m_renderData->configs.drawBuffer;

            m_renderData->configs.drawBuffer = nullptr;
            m_renderData->configs.nextElementPointer = nullptr;
        }
    }

    void RenderGLBase::releaseConfigs() {

        LOG_INFO("RenderGLBase::releaseConfigs() m_renderData = '{:p}'", fmt::ptr(m_renderData));

        if (m_renderData) {
            m_renderData->configs = {};
        }
    }

    Shape* RenderGLBase::getShapeById(unsigned int id) {

        auto it = std::find_if (m_objectsList.begin(), m_objectsList.end(), [id](RenderData::Objects* obj) {
            return obj->shape->getID() == id;
        });

        return it == m_objectsList.end() ? nullptr : (*it)->shape;
    }

    bool RenderGLBase::hasShapeById(unsigned int id) {
        return getShapeById(id) != nullptr;
    }

}

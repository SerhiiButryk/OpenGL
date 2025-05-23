#include "RenderGLBase.h"

#include <common/Log.h>
#include <opengl/render/Renderer.h>

namespace xengine {

    RenderGLBase::RenderGLBase() {
        // TODO: Might not be a good approach but it's a simple way !
        static Renderer renderer;
        m_renderer = &renderer;
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

    void RenderGLBase::begin(RenderData* data) {
        setData(data);
    }

    void RenderGLBase::setShader(const std::string &filePath) {
        std::string path = m_renderData->configs.assetsPath + "/shader/" + filePath;
        m_renderData->shader = new Shader(path);
    }

    void RenderGLBase::setTexture(const std::string &filePath, const std::string& textureName) {

        std::string path = m_renderData->configs.assetsPath + "/textures/" + filePath;
        m_renderData->texture = new Texture(path);

        m_renderData->texture->bind(0 /* Slot */);

        m_renderData->shader->setTexture(textureName, 0 /* Slot */);
    }

    void RenderGLBase::setIndexBuffer(IndexBuffer *ib, uint32_t maxSize) const {

        if (maxSize == 0) {
            maxSize = RenderData::DEFAULT_INDEX_BUFF_SIZE;
        }

        LOG_INFO("RenderCommand::prepareIndexBuffer() creating a buffer with size = {}", maxSize);

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

        ib->bind();
        ib->fill(indices, maxSize);
    }

    void RenderGLBase::end() {

        m_renderData->vertexArray = new VertexArray();
        m_renderData->vertexBuffer = new VertexBuffer();

        m_renderData->vertexArray->bind();
        m_renderData->vertexBuffer->bind();

        m_renderData->vertexBuffer->createAndInitialize(nullptr, VERTEX_TOTAL_SIZE(m_renderData->configs.vertexCount), true);

        /*
            Bind vertex buffer and layout into array buffer
        */

        BufferLayout layout = Vertex::getLayout();
        m_renderData->vertexArray->add(*m_renderData->vertexBuffer, layout);

        m_renderData->indexBuffer = new IndexBuffer();

        setIndexBuffer(m_renderData->indexBuffer, m_renderData->configs.indexBufferMaxSize);

    }

}

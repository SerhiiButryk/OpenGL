#include "RenderDirectorBase.h"

#include <common/Log.h>
#include <opengl/render/Renderer.h>

namespace xengine {

    RenderDirectorBase::RenderDirectorBase() {
        // TODO: Might not be a good approach but it's a simple way !
        static Renderer renderer;
        m_renderer = &renderer;
    }

    void RenderDirectorBase::batch(Shape& shape) {

        auto* srcPointer = shape.getBuffer();
        auto* destPointer = (Vertex*) m_renderData->configs.pointerStart;

        for (int i = 0; i < shape.getVertexCount(); i++) {
            destPointer->position = srcPointer->position;
            destPointer->color = srcPointer->color;
            destPointer->texCoord = srcPointer->texCoord;
            destPointer->texIndex = srcPointer->texIndex;

            destPointer++;
            srcPointer++;
        }

        m_renderData->configs.pointerStart = destPointer;
    }

    void RenderDirectorBase::createVertexBuffer(unsigned int size) {

        if (m_renderData->configs.drawBuffer == nullptr) {

            if (size == 0) {
                size = RenderData::DEFAULT_VERTEX_BUFF_SIZE;
            }

            LOG_INFO("RenderCommand::createVertexBuffer() creating a buffer with size = {}", size);

            m_renderData->configs.drawBuffer = new Vertex[size]{};
            m_renderData->configs.pointerStart = m_renderData->configs.drawBuffer;

        }

    }

    void RenderDirectorBase::begin(RenderData* data) {
        setData(data);
    }

    void RenderDirectorBase::prepareShader(const std::string &filePath) {
        std::string path = m_renderData->configs.assetsPath + "/shader/" + filePath;
        m_renderData->shader = new Shader(path);
    }

    void RenderDirectorBase::prepareTexture(const std::string &filePath, const std::string& textureName) {

        std::string path = m_renderData->configs.assetsPath + "/textures/" + filePath;
        m_renderData->texture = new Texture(path);

        m_renderData->texture->bind(0 /* Slot */);

        m_renderData->shader->setTexture(textureName, 0 /* Slot */);
    }

    void RenderDirectorBase::prepareIndexBuffer(IndexBuffer *ib, uint32_t maxSize) const {

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

    void RenderDirectorBase::end() {

        m_renderData->vertexArray = new VertexArray();
        m_renderData->vertexBuffer = new VertexBuffer();

        m_renderData->vertexArray->bind();
        m_renderData->vertexBuffer->bind();

        m_renderData->vertexBuffer->fill(nullptr, VERTEX_TOTAL_SIZE(m_renderData->configs.vertexCount), true);

        /*
            Bind vertex buffer and layout into array buffer
        */

        BufferLayout layout = Vertex::getLayout();
        m_renderData->vertexArray->add(*m_renderData->vertexBuffer, layout);

        m_renderData->indexBuffer = new IndexBuffer();

        prepareIndexBuffer(m_renderData->indexBuffer, m_renderData->configs.indexBufferMaxSize);

        /**
         * Create a camera
         */

        // TODO: Revisit this should be configured
        m_renderData->camera = new Camera(-1.6f, 1.6f, -0.9f, 0.9f);
    }

}

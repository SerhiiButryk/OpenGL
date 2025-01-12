#include "RenderDirectorBase.h"

#include <common/Log.h>
#include <opengl/render/Renderer.h>

namespace xengine {

    RenderDirectorBase::RenderDirectorBase() {
        // TODO: Might not de a good approach but it is simple way !
        static Renderer renderer;
        m_renderer = &renderer;
    }

    void RenderDirectorBase::batch(Shape& shape) {

        auto* srcPointer = shape.getBuffer();
        auto* destPointer = (Vertex*) m_renderData->configs.pointer;

        for (int i = 0; i < shape.getVertexCount(); i++) {
            destPointer->position = srcPointer->position;
            destPointer->color = srcPointer->color;
            destPointer->texCoord = srcPointer->texCoord;
            destPointer->texIndex = srcPointer->texIndex;

            destPointer++;
            srcPointer++;
        }

        m_renderData->configs.pointer = destPointer;
    }

    void RenderDirectorBase::createVertexBuffer(unsigned int size) {

        if (m_renderData->configs.drawBuffer == nullptr) {

            if (size == 0) {
                size = RenderData::DEFAULT_VERTEX_BUFF_SIZE;
            }

            LOG_INFO("RenderCommand::createVertexBuffer() creating a buffer with size = {}", size);

            m_renderData->configs.drawBuffer = new Vertex[size]{};
            m_renderData->configs.pointer = m_renderData->configs.drawBuffer;

        }

    }

    void RenderDirectorBase::begin() {

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

    void RenderDirectorBase::prepareMVPMatrix(const std::string &name) {

        /* Calculate and set default MVP matrix for this shader */

        // Projection matrix
        glm::mat4 proj = glm::ortho(0.0f, (float) m_renderData->configs.width, 0.0f, (float) m_renderData->configs.height, -1.0f, 1.0f);

        // View matrix
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        // Model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        // MVP matrix
        glm::mat4 mvp = proj * view * model;

        m_renderData->shader->bind();

        m_renderData->shader->setUniformMat(name, mvp);
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
        // When we end we release resources and delete the command
        if (m_renderData != nullptr) {
            m_renderData->releaseResources();
            delete m_renderData;
            m_renderData = nullptr;
        }
    }

}

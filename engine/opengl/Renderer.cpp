#include "Renderer.h"
#include "shapes/Shape.h"

namespace xengine {

    void Renderer::begin(RenderCommand* command) {

        m_command = command;

        m_command->vertexArray = new VertexArray();
        m_command->vertexBuffer = new VertexBuffer();

        m_command->vertexArray->bind();
        m_command->vertexBuffer->bind();

        m_command->vertexBuffer->fill(nullptr, VERTEX_TOTAL_SIZE(m_command->configs.vertexCount), true);

        /*
            Bind vertex buffer and layout into array buffer
        */

        BufferLayout layout = Vertex::getLayout();
        m_command->vertexArray->add(*m_command->vertexBuffer, layout);

        m_command->indexBuffer = new IndexBuffer();

        prepareIndexBuffer(m_command->indexBuffer, m_command->configs.indexBufferMaxSize);

    }

    void Renderer::prepareShader(const std::string &filePath) {
        m_command->shader = new Shader(filePath);
    }

    void Renderer::prepareTexture(const std::string &filePath, const std::string& textureName) {
        m_command->texture = new Texture(filePath);
        m_command->texture->bind(0 /* Slot */);

        m_command->shader->setTexture(textureName, 0 /* Slot */);
    }

    void Renderer::prepareMVPMatrix(const std::string &name) {
        setMVPMatrix(name, m_command->shader, m_command->configs.width, m_command->configs.height);
    }

    void Renderer::end() {
        clearStates();
    }

    void Renderer::clear() {

        clearStates();

        delete m_command->vertexArray;
        delete m_command->vertexBuffer;
        delete m_command->indexBuffer;
        delete m_command->shader;
        delete m_command->texture;
        delete m_command;

        m_command = nullptr;
    }

    void Renderer::clearScreen(glm::vec4 color) {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::clearStates() const {

        if (m_command->vertexArray) {
            m_command->vertexArray->unbind();
        }

        if (m_command->shader) {
            m_command->shader->unBind();
        }

        if (m_command->indexBuffer) {
            m_command->indexBuffer->unbind();
        }

        if (m_command->vertexBuffer) {
            m_command->vertexBuffer->unbind();
        }
    }

    void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {

        /* Bind everything before making a draw call */

        shader.bind();
        va.bind();
        ib.bind();

        /* Send a draw command */

        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);

    }

    void Renderer::setMVPMatrix(const std::string &name, Shader* shader, int windowWidth, int windowHeight) const {

        /* Calculate and set default MVP matrix for this shader */

        // Projection matrix
        glm::mat4 proj = glm::ortho(0.0f, (float) windowWidth, 0.0f, (float) windowHeight, -1.0f, 1.0f);

        // View matrix
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        // Model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        // MVP matrix
        glm::mat4 mvp = proj * view * model;

        shader->bind();

        shader->setUniformMat(name, mvp);

    }

    void Renderer::prepareIndexBuffer(IndexBuffer *ib, uint32_t maxCount) const {

        uint32_t indices[maxCount] = {};
        uint32_t offset = 0;

        // '4' represents 4 vertices of a single quad
        for (int i = 0; i < maxCount; i += 6 /* Makes up a single quad */) {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset += 4;
        }

        ib->bind();
        ib->fill(indices, maxCount);
    }

    bool Renderer::executeCurrentCommand() {

        m_command->vertexBuffer->update(m_command->configs.drawBuffer, VERTEX_TOTAL_SIZE(m_command->configs.vertexCount));

        auto* va = m_command->vertexArray;
        auto* ib = m_command->indexBuffer;
        auto* shader = m_command->shader;

        draw(*va, *ib, *shader);

        return true;
    }

    void RenderCommand::setConfigs(Configs configs) {
        this->configs = configs;
    }
}

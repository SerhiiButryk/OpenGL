#include "Renderer.h"

namespace xengine {

    void RenderCommand::begin() {

        renderer = new Renderer();

        vertexArray = new VertexArray();
        vertexBuffer = new VertexBuffer();

        vertexArray->bind();
        vertexBuffer->bind();

        static constexpr int VERTEX_COUNT = 4;

        vertexBuffer->fill(nullptr, SHAPE_BUFFER_SIZE(VERTEX_COUNT), true);

        /*
         Bind vertex buffer and layout into array buffer
        */

        BufferLayout layout = renderer->getLayoutSpecificationForVertex();
        vertexArray->add(*vertexBuffer, layout);

        indexBuffer = new IndexBuffer();
        renderer->prepareIndexBuffer(indexBuffer);

    }

    void RenderCommand::prepareShader(const std::string &filePath, int w, int h) {

        shader = new Shader(filePath);

        renderer->setMVPMatrix("u_MVP", shader, w, h);
    }

    void RenderCommand::prepareTexture(const std::string &filePath) {

        texture = new Texture(filePath);
        texture->bind(0 /* Slot */);

        shader->setTexture("u_Texture", 0 /* Slot */);
    }

    void RenderCommand::end() {

        renderer->clearStates(vertexArray, shader, vertexBuffer, indexBuffer);
    }

    void RenderCommand::clear() {
        delete renderer;
        delete vertexArray;
        delete vertexBuffer;
        delete indexBuffer;
        delete shader;
        delete texture;
    }

    void RenderCommand::execute(float* buffer) {

        static constexpr int VERTEX_COUNT = 4;

        vertexBuffer->update(buffer, SHAPE_BUFFER_SIZE(VERTEX_COUNT));

        renderer->draw(*vertexArray, *indexBuffer, *shader);
    }

    void Renderer::clean(float red, float green, float blue, float alpha) const {

        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::clearStates(VertexArray *va, Shader *shader, VertexBuffer *vb, IndexBuffer *ib) const {

        if (va) {
            va->unbind();
        }

        if (shader) {
            shader->unBind();
        }

        if (ib) {
            ib->unbind();
        }

        if (vb) {
            vb->unbind();
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

    BufferLayout Renderer::getLayoutSpecificationForVertex() {

        Vertex vertex = {};

        BufferLayout layout;
        // Order is very important here. Should reflect the vertex data structure
        layout.add({VERTEX_ELEMENT_SIZE_FLOAT(vertex.positions), GL_FLOAT, GL_FALSE});
        layout.add({VERTEX_ELEMENT_SIZE_FLOAT(vertex.color), GL_FLOAT, GL_FALSE});
        layout.add({VERTEX_ELEMENT_SIZE_FLOAT(vertex.textureCoord), GL_FLOAT, GL_FALSE});
        layout.add({VERTEX_ELEMENT_SIZE_FLOAT(vertex.textureId), GL_FLOAT, GL_FALSE});

        return layout;
    }

    void Renderer::prepareIndexBuffer(IndexBuffer *ib) const {

        const int indicesSize = 2 * 3;
        uint32_t indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        ib->bind();
        ib->fill(indices, indicesSize);

    }
}

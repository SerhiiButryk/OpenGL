#include "DynamicBatching.h"

#include <common/Log.h>
#include <opengl/Renderer.h>
#include <imgui/imgui.h>
#include <opengl/Textures.h>
#include <opengl/shapes/Rectangle.h>

static xengine::Renderer *renderer = nullptr;
static xengine::VertexArray *vertexArray = nullptr;
static xengine::VertexBuffer *vertexBuffer = nullptr;
static xengine::IndexBuffer *indexBuffer = nullptr;
static xengine::Shader *shader = nullptr;
static xengine::Texture *textures = nullptr;

namespace test {

    void DynamicBatching::onCreate(Application *app) {

        using namespace xengine;

        vertexArray = new VertexArray();
        vertexBuffer = new VertexBuffer();

        BufferLayout layout;
        layout.add({2, GL_FLOAT, GL_FALSE});
        layout.add({4, GL_FLOAT, GL_FALSE});
        layout.add({2, GL_FLOAT, GL_FALSE});
        layout.add({1, GL_FLOAT, GL_FALSE});

        vertexArray->bind();
        vertexBuffer->bind();

        vertexBuffer->fill(nullptr, 8 * sizeof(Vertex), true);

        /*
            Bind vertex buffer and layout into array buffer
        */

        vertexArray->add(*vertexBuffer, layout);

        const int indicesSize = 4 * 3;
        uint32_t indices[] = {
            0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            6, 7, 4
        };

        indexBuffer = new IndexBuffer();

        indexBuffer->bind();
        indexBuffer->fill(indices, indicesSize);

        // Projection matrix
        glm::mat4 proj = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f, -1.0f, 1.0f);

        // View matrix
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        // Model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        // MVP matrix
        glm::mat4 mvp = proj * view * model;

        std::string resPath = app->getResourcePath();
        shader = new Shader(resPath + "/shader/Basic_2.shader");

        shader->bind();

        shader->setUniformMat("u_MVP", mvp);

        textures = new Texture(resPath + "/textures/test.png");
        textures->bind(0 /* Slot */);

        shader->setTexture("u_Texture", 0 /* Slot */);

        renderer = new Renderer();

        /* Clear all states */

        vertexArray->unbind();
        shader->unBind();
        vertexBuffer->unbind();
        indexBuffer->unbind();
    }

    void DynamicBatching::onDestroy() {
        delete renderer;
        delete vertexArray;
        delete vertexBuffer;
        delete indexBuffer;
        delete shader;
        delete textures;
    }

    void DynamicBatching::onBeforeRender() {
    }

    void DynamicBatching::onRender() {

        using namespace xengine;

        Rectangle rect_1({0.0f, 0.0f}, 100.0f, 100.0f);
        Rectangle rect_2({200.0f, 0.0f}, 100.0f, 100.0f);

        // Apply changes
        // rect_1.setColor({1.0f, 0.0f, 0.0f, 1.0f });
        // rect_1.setTextureIndex(-1.0f);
        // rect_1.update();

        // rect_2.setColor({0.0f, 1.0f, 0.0f, 1.0f });
        // rect_2.setTextureIndex(-1.0f);
        // rect_2.update();

        Rectangle::VertexData arr1 = rect_1.getBuffer();
        Rectangle::VertexData arr2 = rect_2.getBuffer();

        std::array<Vertex, 8> arr3 = {};

        std::copy(arr1.begin(), arr1.end(), arr3.begin());
        std::copy(arr2.begin(), arr2.end(), arr3.begin() + 4);

        vertexBuffer->update((float*) arr3.data(), 8 * sizeof(Vertex));

        renderer->draw(*vertexArray, *indexBuffer, *shader);
    }
}

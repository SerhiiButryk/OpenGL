#include "DynamicBatching.h"

#include <common/Log.h>
#include <opengl/Renderer.h>
#include <imgui/imgui.h>
#include <opengl/Textures.h>
#include <ui/Widgets.h>

static xengine::Renderer *renderer = nullptr;
static xengine::VertexArray *vertexArray = nullptr;
static xengine::VertexBuffer *vertexBuffer = nullptr;
static xengine::IndexBuffer *indexBuffer = nullptr;
static xengine::Shader *shader = nullptr;
static xengine::Textures *textures = nullptr;

namespace test {

    void DynamicBatching::onCreate(Application *app) {

        using namespace xengine;

        struct Vertex {
            float positions[2];
            float color[4];
            float textureCoord[2];
            float textureId[1];
        };

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

        textures = new Textures(resPath + "/textures/test.png");
        textures->bind(0 /* Slot */);

        shader->setUniformTexture("u_Texture", 0 /* Slot */);

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

        float positions[] = {
            // first square
            0.0f, 0.0f, /* position */ 0.0f, 0.0f, 1.0f, 1.0f, /* color */ 0.0f, 0.0f, /* texture */ 0.0f,
            /* texture id */ // 0
            100.0f, 0.0f, /* position */ 0.0f, 0.0f, 1.0f, 1.0f, /* color */ 1.0f, 0.0f, /* texture */ 0.0f,
            /* texture id */ // 1
            100.f, 100.0f, /* position */ 0.0f, 0.0f, 1.0f, 1.0f, /* color */ 1.0f, 1.0f, /* texture */ 0.0f,
            /* texture id */ // 2
            0.0f, 100.0f, /* position */ 0.0f, 0.0f, 1.0f, 1.0f, /* color */ 0.0f, 1.0f, /* texture */ 0.0f,
            /* texture id */ // 3

            // second square
            200.0f, 0.0f, /* position */ 0.0f, 1.0f, 0.0f, 1.0f, /* color */ 0.0f, 0.0f, /* texture */ 0.0f,
            /* texture id */ // 4
            300.0f, 0.0f, /* position */ 0.0f, 1.0f, 0.0f, 1.0f, /* color */ 1.0f, 0.0f, /* texture */ 0.0f,
            /* texture id */ // 5
            300.f, 100.0f, /* position */ 0.0f, 1.0f, 0.0f, 1.0f, /* color */ 1.0f, 1.0f, /* texture */ 0.0f,
            /* texture id */ // 6
            200.0f, 100.0f, /* position */ 0.0f, 1.0f, 0.0f, 1.0f, /* color */ 0.0f, 1.0f, /* texture */
            0.0f /* texture id */ // 7
        };

        vertexBuffer->update(positions, sizeof(positions));

        renderer->draw(*vertexArray, *indexBuffer, *shader);
    }
}
#include "BatchingTest.h"

#include <public/XEngine.h>

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/string_cast.hpp"

static xengine::Renderer renderer;

static xengine::VertexArray *vertexArray = nullptr;
static xengine::VertexBuffer *vertexBuffer = nullptr;
static xengine::IndexBuffer *indexBuffer = nullptr;
static xengine::Shader *shader = nullptr;
static xengine::Texture *textures = nullptr;

namespace test {

    void BatchingTest::onCreate(Application *app) {

        using namespace xengine;

        const int size = 8 * 9;
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

        vertexArray = new VertexArray();
        vertexBuffer = new VertexBuffer();

        BufferLayout layout;
        layout.add({2, GL_FLOAT, GL_FALSE});
        layout.add({4, GL_FLOAT, GL_FALSE});
        layout.add({2, GL_FLOAT, GL_FALSE});
        layout.add({1, GL_FLOAT, GL_FALSE});

        vertexArray->bind();
        vertexBuffer->bind();

        vertexBuffer->fill(positions, size * sizeof(float));

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

        float w = app->getWidth();
        float h = app->getHeight();

        // Projection matrix
        glm::mat4 proj = glm::ortho(0.0f, w, 0.0f, h, -1.0f, 1.0f);
        LOG_INFO("Proj matrix {}", glm::to_string(proj));

        // View matrix
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        LOG_INFO("View matrix {}", glm::to_string(view));

        // Model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        LOG_INFO("Model matrix {}", glm::to_string(model));

        glm::mat4 scaling = glm::scale(glm::mat4(1), glm::vec3(2,2,2));
        LOG_INFO("Scaling matrix {}", glm::to_string(scaling));

        // MVP matrix
        glm::mat4 mvp = proj * view * model;

        std::string resPath = app->getResourcePath();
        shader = new Shader(resPath + "/shader/Basic_2.shader");

        shader->bind();

        shader->setUniformMat("u_MVP", mvp);

        textures = new Texture(resPath + "/textures/test.png");
        textures->bind(0 /* Slot */);

        shader->setTexture("u_Texture", 0 /* Slot */);

        /* Clear all states */

        vertexArray->unbind();
        shader->unBind();
        vertexBuffer->unbind();
        indexBuffer->unbind();
    }

    void BatchingTest::onDestroy() {
        delete vertexArray;
        delete vertexBuffer;
        delete indexBuffer;
        delete shader;
        delete textures;
    }

    void BatchingTest::onBeforeRender() {
    }

    void BatchingTest::onRender() {

        using namespace xengine;

        RenderData renderData;
        renderData.shader = shader;
        renderData.vertexArray = vertexArray;
        renderData.indexBuffer = indexBuffer;
        renderData.texture = textures;
        renderData.vertexBuffer = vertexBuffer;

        renderer.setData(&renderData);

        renderer.drawRectangle();
    }
}

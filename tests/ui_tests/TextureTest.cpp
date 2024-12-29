#include "TextureTest.h"

#include <common/Log.h>
#include <opengl/Renderer.h>
#include <imgui/imgui.h>
#include <opengl/Textures.h>
#include <ui/Widgets.h>

static xengine::Renderer* renderer = nullptr;
static xengine::VertexArray* vertexArray = nullptr;
static xengine::VertexBuffer* vertexBuffer = nullptr;
static xengine::IndexBuffer* indexBuffer = nullptr;
static xengine::Shader* shader = nullptr;
static xengine::Texture* textures = nullptr;

namespace test {

    void TextureTest::onCreate(Application* app) {

        using namespace xengine;

        const int size = 4 * 4;

        float positions[size] = {
            // all positions    texture coordinates
            0.0f, 0.0f,         0.0f,  0.0f, // 0
            100.0f, 0.0f,       1.0f,  0.0f, // 1
            100.f, 100.0f,      1.0f,  1.0f, // 2
            0.0f, 100.0f,       0.0f,  1.0f, // 3
        };

        vertexArray = new VertexArray();
        vertexBuffer = new VertexBuffer();

        /*
           Specify the layout of the data.
        */

        BufferLayout layout;
        layout.add({2, GL_FLOAT, GL_FALSE});
        layout.add({2, GL_FLOAT, GL_FALSE});

        vertexArray->bind();

        vertexBuffer->bind();
        vertexBuffer->fill(positions, size * sizeof(float));

        /*
            Bind vertex buffer and layout into array buffer
        */

        vertexArray->add(*vertexBuffer, layout);

        /*
            Generate & bind index buffer object
        */

        const int indicesSize = 6;
        uint32_t indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        indexBuffer = new IndexBuffer();

        indexBuffer->bind();
        indexBuffer->fill(indices, indicesSize);

        // Projection matrix
        // 3 x 2 aspect ratio which is
        // 1.5 * 2 = 3
        // 1 * 2 = 2
        // glm::mat4 proj = glm::ortho(-1.5f, 1.5f, -1.0f, 1.0f, -1.0f, 1.0f);

        // Projection matrix
        glm::mat4 proj = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f, -1.0f, 1.0f);

        // View matrix
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        // Model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        // MVP matrix
        glm::mat4 mvp = proj * view * model;

        /* Create a shader */
        std::string resPath = app->getResourcePath();
        shader = new Shader(resPath + "/shader/Basic_texture.shader");

        shader->bind();
        // Set a color in RGB format
        // shader.setUniform("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
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

    void TextureTest::onDestroy() {
        delete renderer;
        delete vertexArray;
        delete vertexBuffer;
        delete indexBuffer;
        delete shader;
        delete textures;
    }

    void TextureTest::onBeforeRender() {
    }

    static float x_Shift = 0.0f;
    static float y_Shift = 0.0f;

    void onClick(const char* text) {
        LOG_INFO("onClick() button with '{}' name is clicked", text);
        float base = 10;
        if (strcasecmp(text, "Left") == 0) {
            x_Shift -= base;
        } else if (strcasecmp(text, "Right") == 0) {
            x_Shift += base;
        } else if (strcasecmp(text, "Up") == 0) {
            y_Shift += base;
        } else if (strcasecmp(text, "Down") == 0) {
            y_Shift -= base;
        }
        LOG_INFO("onClick() {} {}", x_Shift, y_Shift);
    }

    void TextureTest::onRender() {

        using namespace xengine;

        // Projection matrix
        // Converting to a pixel space = 1200 x 800
        glm::mat4 proj = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f, -1.0f, 1.0f);

        // View matrix
        // Moving object to the right
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        // Model matrix
        // Moving object right and up for 200 pixels
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + x_Shift, 0.0f + y_Shift, 0.0f));

        // MVP matrix
        glm::mat4 mvp = proj * view * model;

        shader->setUniformMat("u_MVP", mvp);

        // shader.setUniform("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        renderer->draw(*vertexArray, *indexBuffer, *shader);

        ImGui::Spacing();

        addButton("Left", &onClick, false);
        addButton("Right", &onClick);
        addButton("Up", &onClick);
        addButton("Down", &onClick);
    }
}

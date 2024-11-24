#include "TestUI.h"

#include <Application.h>
#include <common/Log.h>
#include <opengl/Renderer.h>
#include <opengl/Textures.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

static xengine::Renderer* renderer = nullptr;
static xengine::VertexArray* vertexArray = nullptr;
static xengine::VertexBuffer* vertexBuffer = nullptr;
static xengine::IndexBuffer* indexBuffer = nullptr;
static xengine::Shader* shader = nullptr;
static xengine::Textures* textures = nullptr;

const std::string resPath = "../../engine/res";

namespace client {

    void TestUI::onCreate() {

        logInfo("TestUI::onCreateUI");

        using namespace xengine;

        /*
         So what we need here is the next:

         1) We need to create a data and give it to GL.
         2) We need to describe this data. In other words, what to draw and how to draw.
         3) We need to issue a draw call.
       */

        const int size = 4 * 4;
        // float positions[size] = {
        //     // positions    texture coordinates
        //     -0.5f, -0.5f,    0.0f, 0.0f, // 0
        //      0.5f, -0.5f,    1.0f, 0.0f, // 1
        //     0.5f, 0.5f,      1.0f, 1.0f, // 2
        //     -0.5f, 0.5f,     0.0f, 1.0f, // 3
        // };

        float positions[size] = {
            // positions    texture coordinates
            0.0f, 0.0f, 0.0f, 0.0f, // 0
            100.0f, 0.0f, 1.0f, 0.0f, // 1
            100.f, 100.0f, 1.0f, 1.0f, // 2
            0.0f, 100.0f, 0.0f, 1.0f, // 3
        };

        // float positions[size] = {
        //     // positions    texture coordinates
        //     100.0f, 100.0f,    0.0f, 0.0f, // 0
        //      200.0f, 100.0f,    1.0f, 0.0f, // 1
        //     200.f, 200.0f,      1.0f, 1.0f, // 2
        //     100.0f, 200.0f,     0.0f, 1.0f, // 3
        // };

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
        // Converting to a pixel space = 1200 x 800
        glm::mat4 proj = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f, -1.0f, 1.0f);

        // View matrix
        // Moving object to the right
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 0.0f, 0.0f));

        // Model matrix
        // Moving object right and up for 200 pixels
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f));

        // MVP matrix
        glm::mat4 mvp = proj * view * model;

        /* Create a shader */
        shader = new Shader(resPath + "/shader/Basic_texture.shader");

        shader->bind();
        // Set a color in RGB format
        // shader.setUniform("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
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

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) m_app->getMainApplication()->getWindow(), true);

        const char* glsl_version = "#version 130";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void TestUI::onRender() {

        // Nice grey color
        float red = 192 / 255.0;
        float green = 194 / 255.0;
        float blue = 201 / 255.0;

        // Clear screen to some initial starting color,
        // so we can draw things again from the begging
        renderer->clean(red, green, blue, 1.0f);

        // shader.setUniform("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        renderer->draw(*vertexArray, *indexBuffer, *shader);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Test application");

            ImGui::Button("Test button");

            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void TestUI::onDestroy() {

        logInfo("TestUI::onDestroyUI");

        delete renderer;
        delete vertexArray;
        delete vertexBuffer;
        delete indexBuffer;
        delete shader;
        delete textures;

        // Clear ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

}

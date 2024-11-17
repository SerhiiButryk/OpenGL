#include "MainThread.h"

#include <common/Log.h>
#include <opengl/GLEngine.h>
#include <opengl/external/GLFBridge.h>
#include "common/Exception.h"
#include "opengl/IndexBuffer.h"
#include "opengl/VertexBuffer.h"
#include "opengl/VertexArray.h"
#include "opengl/Layout.h"
#include "opengl/Shader.h"
#include "opengl/Renderer.h"
#include "opengl/Textures.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void MainThread::onCreate() {
    logInfo("MainThread::onCreate");
    // Init our engine
    if (!GLEngine::initEngine()) {
        throwApplicationInitException(ApplicationInitException::WINDOW_CREATION_ERROR);
    }
}

void MainThread::onDestroy() {
    logInfo("MainThread::onDestroy");
    // Clean up
    if (m_ui_created) {
        logInfo("MainThread::onDestroy destroy UI");
        // Clear ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    // Clean our engine
    GLFBridge::cleanup();
}

void MainThread::loop(MainApplication* app) {

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
        0.0f, 0.0f,    0.0f, 0.0f, // 0
        100.0f, 0.0f,    1.0f, 0.0f, // 1
        100.f, 100.0f,      1.0f, 1.0f, // 2
        0.0f, 100.0f,     0.0f, 1.0f, // 3
    };

    // float positions[size] = {
    //     // positions    texture coordinates
    //     100.0f, 100.0f,    0.0f, 0.0f, // 0
    //      200.0f, 100.0f,    1.0f, 0.0f, // 1
    //     200.f, 200.0f,      1.0f, 1.0f, // 2
    //     100.0f, 200.0f,     0.0f, 1.0f, // 3
    // };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer;

    /*
       Specify the layout of the data.
    */

    BufferLayout layout;
    layout.add({2, GL_FLOAT, GL_FALSE });
    layout.add({2, GL_FLOAT, GL_FALSE });

    vertexArray.bind();

    vertexBuffer.bind();
    vertexBuffer.fill(positions, size * sizeof(float));

    /*
        Bind vertex buffer and layout into array buffer
    */

    vertexArray.add(vertexBuffer, layout);

    /*
        Generate & bind index buffer object
    */

    const int indicesSize = 6;
    uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    IndexBuffer indexBuffer;

    indexBuffer.bind();
    indexBuffer.fill(indices, indicesSize);

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

    // Shader shader("../engine/res/shader/Basic.shader");
    Shader shader("../engine/res/shader/Basic_texture.shader");

    shader.bind();
    // Set a color in RGB format
    // shader.setUniform("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    shader.setUniformMat("u_MVP", mvp);

    Textures textures("../engine/res/textures/test.png");
    textures.bind(0 /* Slot */);

    shader.setUniformTexture("u_Texture", 0 /* Slot */);

    /* Clear all states */

    vertexArray.unbind();
    shader.unBind();
    vertexBuffer.unbind();
    indexBuffer.unbind();

    Renderer renderer;

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(app->getWindow(), true);

    m_ui_created = true;

    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(app->getWindow()))
    {
        // Nice grey color
        float red = 192 / 255.0;
        float green = 194 / 255.0;
        float blue = 201 / 255.0;

        // Clear screen to some initial starting color,
        // so we can draw things again from the begging
        renderer.clean(red, green, blue, 1.0f);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // shader.setUniform("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        renderer.draw(vertexArray, indexBuffer, shader);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /*
           Swap front and back buffers
           Back buffer is a buffer which user cannot see.
           Front buffer is a buffer which user sees and which the window is using.
           We draw to the back buffer, and then we swap the buffer to reflect
           things on the screen.
        */

        glfwSwapBuffers(app->getWindow());

        /* Get user or process events */

        glfwPollEvents();
    }
}

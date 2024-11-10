/* Glew is included first because it loads and provides OpenGL APIs to use later */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "opengl/IndexBuffer.h"
#include "opengl/VertexBuffer.h"
#include "opengl/VertexArray.h"
#include "opengl/Layout.h"
#include "opengl/window/Window.h"
#include "opengl/external/GLFBridge.h"
#include "common/Log.h"
#include "opengl/Shader.h"
#include <opengl/GLEngine.h>
#include "opengl/Renderer.h"
#include "opengl/Textures.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main()
{
    if (!GLEngine::initEngine()) {
        return 1;
    }

    /* Create a window and its OpenGL context */

    Window window;

    // 3 x 2 aspect ratio
    int width = 1200;
    int height = 800;
    const char* title = "Application";

    if (!window.create(title, width, height)) {
        window.destroy();
        GLFBridge::cleanup();
        return 1;
    }

    // Log debug info
    GLEngine::printInfo();
    GLEngine::setDebugCallback();
    // Blending
    GLEngine::setBlending(true);
    GLEngine::setBlendingMode();

    /* 
        So what we need here is the next:
        
        1) We need to specify a data and give it to GL.
        2) We need to describe this data. In other words, what to draw and how to draw.
        2) Issue a draw call.
 
    */

    const int size = 4 * 4;
    float positions[size] = {
        // positions    texture coordinates
        -0.5f, -0.5f,    0.0f, 0.0f, // 0
         0.5f, -0.5f,    1.0f, 0.0f, // 1
        0.5f, 0.5f,      1.0f, 1.0f, // 2
        -0.5f, 0.5f,     0.0f, 1.0f, // 3
    };

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

    // 3 x 2 aspect ratio which is
    // 1.5 * 2 = 3
    // 1 * 2 = 2
    glm::mat4 proj = glm::ortho(-1.5f, 1.5f, -1.0f, 1.0f, -1.0f, 1.0f);

    /* Create a shader */

    // Shader shader("../engine/res/shader/Basic.shader");
    Shader shader("../engine/res/shader/Basic_texture.shader");

    shader.bind();
    // Set a color in RGB format
    // shader.setUniform("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    shader.setUniformMat("u_MVP", proj);

    Textures textures("../engine/res/textures/test.png");
    textures.bind(0 /* Slot */);

    shader.setUniformTexture("u_Texture", 0 /* Slot */);

    /* Clear all states */

    vertexArray.unbind();
    shader.unBind();
    vertexBuffer.unbind();
    indexBuffer.unbind();

    Renderer renderer;

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose((GLFWwindow*)window.getWindow()))
    {
        // Nice grey color
        float red = 192 / 255.0;
        float green = 194 / 255.0;
        float blue = 201 / 255.0;

        // Clear screen to some initial starting color, 
        // so we can draw things again from the begging
        renderer.clean(red, green, blue, 1.0f);

        // shader.setUniform("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        
        renderer.draw(vertexArray, indexBuffer, shader);

        /* 
           Swap front and back buffers 
           Back buffer is a buffer which user cannot see.
           Front buffer is a buffer which user sees and which the window is using.
           We draw to the back buffer, and then we swap the buffer to reflect 
           things on the screen.
        */

        glfwSwapBuffers((GLFWwindow*) window.getWindow());

        /* Get user or process events */

        glfwPollEvents();
    }

    /* Release resources */

    window.destroy();
    GLFBridge::cleanup();

    logInfo("Program has finished");

    return 0;
}
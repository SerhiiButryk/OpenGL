/* Glew is included first because it loads and provides OpenGL APIs to use later */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void printGLInfo();

int main(void)
{
    /* Initialize the library */

    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    int width = 1200;
    int height = 800;
    const char* title = "App";

    /* Create a windowed mode window and its OpenGL context */

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */

    glfwMakeContextCurrent(window);

    /* Initializing GLEW */

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << "Error: failed to init GLEW lib\n";
        return -1;
    }

    /* Print OpenGL info */ 

    printGLInfo();

    /*
        So what we need here is next.
        We want to tell GL what to draw and how to draw.
        For that we need to specify a data and give it to GL.

    */

    /* Create a vertex buffer. A vertex in this context just means a position or a point of a shape. */

    const int size = 6;
    float positions[size] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f
    };
    
    unsigned int buffer;
    glGenBuffers(1 /* Create 1 buffer */, &buffer /* buffer name or buffer id */);

    /* Select vertex buffer */

    glBindBuffer(GL_ARRAY_BUFFER /* Buffer type */, buffer /* Buffer name */);
    
    /* Fill a vertex buffer with data */
    
    glBufferData(
        GL_ARRAY_BUFFER /* Buffer type */,
        size * sizeof(float) /* Buffer size */,
        positions,
        GL_STATIC_DRAW /* A hint for GPU see docs for details */
    );

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT);

        /* Send a draw command */

        glDrawArrays(GL_TRIANGLES, 0 /* Staring from the first point or vertex */, 3 /* Says that we have 3 points or 3 vetesies */);

        /* Swap front and back buffers */

        glfwSwapBuffers(window);

        /* Poll for and process events */

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void printGLInfo() 
{
    auto version = glGetString(GL_VERSION);
    if (version != nullptr)
        std::cout << "GL version: " << version << std::endl;

    auto vendor = glGetString(GL_VENDOR);
    if (vendor != nullptr)
        std::cout << "GL vendor: " << vendor << std::endl;

    auto render = glGetString(GL_RENDER);
    if (render != nullptr)
        std::cout << "GPU name: " << render << std::endl;
}
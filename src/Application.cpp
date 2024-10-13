/* Glew is included first because it loads and provides OpenGL APIs to use later */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>

#include "opengl/IndexBuffer.h"
#include "opengl/VertexBuffer.h"
#include "opengl/VertexArray.h"
#include "opengl/Layout.h"
#include "opengl/window/Window.h"
#include "opengl/external/GLFBridge.h"
#include "common/Log.h"

void printGLInfo();

struct ShaderFile
{
    std::string vertexShader;
    std::string fragmentShader;
};

static unsigned int compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)alloca(length * sizeof(char));

        glGetShaderInfoLog(id, length, &length, message);

        logInfo("Failed to compile: ", message);

        glDeleteShader(id);

        return 0;
    }

    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

static ShaderFile readShaders()
{
    std::filesystem::path current_path = std::filesystem::current_path();

    logInfo("Working dir: ", current_path);

    std::string file_name = "res/shader/Basic.shader";
    std::ifstream istream(file_name);

    std::string line;
    std::stringstream vertexShaderStream;
    std::stringstream fragmentShaderStream;

    std::stringstream* current = nullptr;

    while (std::getline(istream, line))
    {
        if (line.find("#vertex_shader") != std::string::npos)
        {
            current = &vertexShaderStream;
        } 
        else if (line.find("#fragment_shader") != std::string::npos) 
        {
            current = &fragmentShaderStream;
        }
        else 
        {
            current->write(line.c_str(), line.size());
            current->put('\n');
        }
    }

    ShaderFile shaderFile { vertexShaderStream.str(), fragmentShaderStream.str() };

    logInfo("Vertex shader: \n \"", shaderFile.vertexShader, "\"");
    logInfo("Fragment shader: \n \"", shaderFile.fragmentShader, "\"");

    return shaderFile;
}

int main(void)
{
    /* Initializing the GLFW library */

    bool result = GLFBridge::init();

    if (!result) {
        GLFBridge::cleanup();
        return 1;
    }

    /* Create a window and its OpenGL context */

    Window window;

    int width = 1200;
    int height = 800;
    const char* title = "Application";

    result = window.create(title, width, height);

    if (!result)
    {
        GLFBridge::cleanup();
        return 1;
    }

    /*
        Get view buffer size information
    */
    int bufferWidth, bufferHeight;

    glfwGetFramebufferSize((GLFWwindow*) window.getWindow(), &bufferWidth, &bufferHeight);

    logInfo("View port information: ", bufferWidth, bufferHeight);

    /* Set the window's OpenGL context to be the current on this thread */

    glfwMakeContextCurrent((GLFWwindow*) window.getWindow());

    /* Enable modern extension features  */

    glewExperimental = GL_TRUE;

    /* Initializing the GLEW library */

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Error: glewInit failed, something is seriously wrong. */
        logError("Error: failed to init GLEW library");
        window.destroy();
        GLFBridge::cleanup();
        return 1;
    }

    /* Setup view ports in OpenGL */

    glViewport(0, 0, bufferWidth, bufferHeight);

    /* Log OpenGL debug info */ 

    printGLInfo();

    /* 
        So what we need here is the next:
        
        1) We need to specify a data and give it to GL.
        2) We need to describe this data. In other words, what to draw and how to draw.
        2) Issue a draw call.
 
    */

    const int size = 8;
    float positions[size] = {
        -0.5f, -0.5f, // 0
        0.0f, -0.5f, // 1
        0.0f, 0.5f, // 2
        -0.5f, 0.5f // 3
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer;

    /*
       Specify the layout of the data.
    */

    BufferLayout layout;
    layout.add({2, GL_FLOAT, GL_FALSE,  sizeof(float) * 2});

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
    indexBuffer.fill(indices, indicesSize * sizeof(uint32_t));

    /* Create a shader program */

    ShaderFile shaderFile = readShaders();

    unsigned int shader = createShader(shaderFile.vertexShader, shaderFile.fragmentShader);

    glUseProgram(shader);

    /* Set uniform */

    int location = glGetUniformLocation(shader, "u_Color"); // Get the id of uniform variable
    glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f); // Set a color in RGB format

    /* Clear all states */

    vertexArray.unbind();
    glUseProgram(0);
    vertexBuffer.unbind();
    indexBuffer.unbind();

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose((GLFWwindow*)window.getWindow()))
    {
        // Nice grey color
        float red = 192 / 255.0;
        float green = 194 / 255.0;
        float blue = 201 / 255.0;

        // Clear screen to some initial starting color, 
        // so we can draw things again from the begging

        glClearColor(red, green, blue, 1.0f /* alpha */);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Bind everything before sending a draw call */

        glUseProgram(shader);
        glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);
        
        vertexArray.bind();
        indexBuffer.bind();

        /* Send a draw command */

        glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);

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

    glDeleteProgram(shader);

    /* Release resources */

    window.destroy();
    GLFBridge::cleanup();

    logInfo("Program has finished");

    return 0;
}

void printGLInfo() 
{
    auto version = glGetString(GL_VERSION);
    if (version != nullptr)
        logInfo("GL version: ", version);

    auto vendor = glGetString(GL_VENDOR);
    if (vendor != nullptr)
        logInfo("GL vendor: ", vendor);

    auto render = glGetString(GL_RENDER);
    if (render != nullptr)
        logInfo("GPU name: ", render);
}
/* Glew is included first because it loads and provides OpenGL APIs to use later */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <time.h>

#include "opengl/IndexBuffer.h"
#include "opengl/VertexBuffer.h"

void printGLInfo();

std::string time_in_HH_MM_SS_MMM()
{
    using namespace std::chrono;

    // get current time
    auto now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    time_t t = time(NULL);
    std::tm bt;
    localtime_s(&bt, &t);

    std::ostringstream oss;

    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

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

        std::cout << "Failed to compile: " << std::endl;
        std::cout << "Message: " << message << std::endl;

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

    std::cout << "\nWorking dir: " << current_path << std::endl;

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

    std::cout << "\nVertex shader: \n" << shaderFile.vertexShader << std::endl;
    std::cout << "\nFragment shader: \n" << shaderFile.fragmentShader << std::endl;

    return shaderFile;
}

int main(void)
{
    /* Initializing the GLFW library */

    if (!glfwInit()) {
        std::cout << "Error: failed to init GLFW library\n";
        glfwTerminate();
        return 1;
    }

    /* Setup OpenGL profile and version */

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a window and its OpenGL context */

    GLFWwindow* window;
    int width = 1200;
    int height = 800;
    const char* title = "Application";

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        std::cout << "Error: failed to create a window\n";
        glfwTerminate();
        return 1;
    }

    /*
        Get view buffer size information
    */
    int bufferWidth, bufferHeight;

    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    std::cout << "View port information: " << bufferWidth << " " << bufferHeight << std::endl;

    /* Set the window's OpenGL context to be the current on this thread */

    glfwMakeContextCurrent(window);

    /* Enable modern extension features  */

    glewExperimental = GL_TRUE;

    /* Initializing the GLEW library */

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Error: glewInit failed, something is seriously wrong. */
        std::cout << "Error: failed to init GLEW library\n";
        glfwDestroyWindow(window);
        glfwTerminate();
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

    /*
        Create a vartex array object
        
        A vao holds a reference of vertex buffer and verter pointer attribs together.
        By changing it we can change vertex buffer and therefore draw a different shape. 
    */
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    /*
        Create a vertex buffer.

        A vertex buffer in this context just means a data to be used for drawing
        a shape on a screen.
    */

    const int size = 8;
    float positions[size] = {
        -0.5f, -0.5f, // 0
        0.0f, -0.5f, // 1
        0.0f, 0.5f, // 2
        -0.5f, 0.5f // 3
    };

    VertexBuffer vertexBuffer;

    vertexBuffer.bind();
    vertexBuffer.fill(positions, size * sizeof(float));

    /*
        At this moment we must specify the layout of the data.
        In other words, what it is and what attributes or properties it has.
        
        To do this we use the below settings.
    */

    glEnableVertexAttribArray(0); 

    /*
        The next functions tell OpenGL that what the attribute index​ 
        will get its attribute data from whatever buffer object is 
        currently bound to GL_ARRAY_BUFFER
    */

    glVertexAttribPointer(0 /* Index of the first vertex data element */, 
        2 /* The number of elements we are using , a kind of 2d coordinates */,
        GL_FLOAT /* Type of the data buffer that we selected */,
        GL_FALSE /* Do not normalize */,
        sizeof(float) * 2 /* Byte size between vertex elements, in our case it's 2 floats so it's 8 bytes */,
        0 /* The pointer to our first vertex attribute. It matches index 0 */);

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

    glBindVertexArray(0);
    glUseProgram(0);
    vertexBuffer.unbind();
    indexBuffer.unbind();

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
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
        
        glBindVertexArray(vao);
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

        glfwSwapBuffers(window);

        /* Get user or process events */

        glfwPollEvents();
    }

    glDeleteProgram(shader);

    /* Release resources */

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Program has finished" << std::endl;

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
#include "GLFBridge.h"

#include "../window/Window.h"
#include "../../common/Log.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool GLFBridge::init()
{
    /* Initializes the GLFW library */

    if (!glfwInit()) {
        logError("GLFBridge::init() failed to init GLFW library");
        return false;
    }

    /* Setup OpenGL profile and version */

    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // No backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Enable forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	return true;
}

void GLFBridge::cleanup()
{
    logInfo("GLFBridge::cleanup()");
    glfwTerminate();
}

bool GLFBridge::createWindow(Window& window, const char* title, int width, int height)
{
    logInfo("GLFBridge::createWindow()");

    GLFWwindow* w = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!w)
    {
        return false;
    }

    window.setWindow(w);

    return true;
}

void GLFBridge::destroyWindow(const Window& window)
{
    logInfo("GLFBridge::destroyWindow()");

    glfwDestroyWindow(static_cast<GLFWwindow *>(window.getWindow()));
}

void GLFBridge::initWindowConfigs(Window& window) {
    /*
      Get view buffer size information
    */
    int bufferWidth, bufferHeight;

    glfwGetFramebufferSize((GLFWwindow*) window.getWindow(), &bufferWidth, &bufferHeight);

    logInfo("GLFBridge::initWindowConfigs() View port information: ", bufferWidth, bufferHeight);

    /* Set the window's OpenGL context to be the current on this thread */

    glfwMakeContextCurrent((GLFWwindow*) window.getWindow());

    window.setBufferSize(bufferWidth, bufferHeight);
}

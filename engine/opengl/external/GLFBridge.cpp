#include "GLFBridge.h"
#include "../window/Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../common/Log.h"

bool GLFBridge::init()
{
    /* Initializes the GLFW library */

    if (!glfwInit()) {
        logError("GLFBridge::init() failed to init GLFW library");
        return false;
    }

    /* Setup OpenGL profile and version */

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

    glfwDestroyWindow((GLFWwindow*)window.getWindow());
}

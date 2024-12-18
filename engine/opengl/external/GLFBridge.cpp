#include "GLFBridge.h"

#include "../../window/Window.h"
#include "../../common/Log.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace xengine {

    /* GLFW error callback */
    static void GLFWErrorCallback(int error, const char* description)
    {
        LOG_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    bool GLFBridge::init()
    {
        glfwSetErrorCallback(GLFWErrorCallback);

        /* Initializes the GLFW library */

        if (!glfwInit()) {
            LOG_ERROR("GLFBridge::init() failed to init GLFW library");
            return false;
        }

        /* Setup OpenGL profile and version */

        // Set minimum OpenGL version
        // TODO: Check what happens if we cannot use 4.5 version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        // No backwards compatibility
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // Enable forward compatibility
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        // Enable OpenGL debug context which may give more info about errors
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

	    return true;
    }

    void GLFBridge::cleanup()
    {
        LOG_INFO("GLFBridge::cleanup()");
        glfwTerminate();
    }

    bool GLFBridge::createWindow(Window& window, const char* title, int width, int height)
    {
        LOG_INFO("GLFBridge::createWindow()");

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
        LOG_INFO("GLFBridge::destroyWindow()");

        glfwDestroyWindow(static_cast<GLFWwindow *>(window.getWindow()));
    }

    void GLFBridge::initWindowConfigs(Window& window) {
        /*
          Get view buffer size information
        */
        int bufferWidth, bufferHeight;

        glfwGetFramebufferSize((GLFWwindow*) window.getWindow(), &bufferWidth, &bufferHeight);

        LOG_INFO("GLFBridge::initWindowConfigs() View port information: '{}' '{}'", bufferWidth, bufferHeight);

        /* Set the window's OpenGL context to be the current on this thread */

        glfwMakeContextCurrent((GLFWwindow*) window.getWindow());

        window.setBufferSize(bufferWidth, bufferHeight);

        // Enable vsync
        glfwSwapInterval(1);
    }

}

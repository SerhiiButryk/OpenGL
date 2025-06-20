#include "PlatformGateWay.h"

#include <common/Log.h>
#include <window/input/Input.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace xengine {

    /* GLFW error callback */
    static void GLFWErrorCallback(int error, const char *description) {
        LOG_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    bool PlatformGateWay::init() {

        glfwSetErrorCallback(GLFWErrorCallback);

        /* Initializes the GLFW library */

        if (!glfwInit()) {
            LOG_ERROR("PlatformGateWay::init() failed to init GLFW library");
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
        glfwWindowHint(GLFW_RESIZABLE, true);

        int major, minor, rev;
        glfwGetVersion(&major, &minor, &rev);
        LOG_INFO("PlatformGateWay::init() GLFW version: {}.{} rev: {}", major, minor, rev);

        return true;
    }

    void PlatformGateWay::cleanup() {
        LOG_INFO("PlatformGateWay::cleanup()");
        glfwTerminate();
    }

    bool PlatformGateWay::createWindow(Window &window, const char *title, int width, int height) {
        LOG_INFO("PlatformGateWay::createWindow()");

        int monitorX = 0, monitorY = 0;
        const GLFWvidmode *videoMode = nullptr;

        GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();

        if (primaryMonitor) {
            // Monitor and display information
            videoMode = glfwGetVideoMode(primaryMonitor);
            glfwGetMonitorPos(primaryMonitor, &monitorX, &monitorY);
        }

        // Window hints
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        GLFWwindow *w = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!w) {
            return false;
        }

#ifndef UNIT_TESTS
        if (videoMode) {
            // Show window in the center
            glfwSetWindowPos(w, monitorX + (videoMode->width - width) / 2, monitorY + (videoMode->height - height) / 2);
        }
        glfwShowWindow(w);
#endif

        window.setWindow(w);

        // Setup other configs
        initWindowConfigs(window);

        return true;
    }

    void PlatformGateWay::destroyWindow(const Window &window) {
        LOG_DEBUG("PlatformGateWay::destroyWindow() p = '{:p}'", fmt::ptr(&window));
        glfwDestroyWindow(static_cast<GLFWwindow *>(window.getWindow()));
        LOG_DEBUG("PlatformGateWay::destroyWindow() done");
    }

    void PlatformGateWay::initWindowConfigs(Window &window) {
        /*
          Get view buffer size information
        */
        int bufferWidth, bufferHeight;

        auto *w = (GLFWwindow *) window.getWindow();

        glfwGetFramebufferSize(w, &bufferWidth, &bufferHeight);

        LOG_INFO("PlatformGateWay::initWindowConfigs() with view ports: '{}' '{}'", bufferWidth, bufferHeight);

        /* Set the window's OpenGL context to be the current on this thread */

        glfwMakeContextCurrent(w);

        // Save and tell OpenGL the size of the rendering window
        window.setBufferSize(bufferWidth, bufferHeight);
        glViewport(0, 0, bufferWidth, bufferHeight);

        // Enable vsync
        // Basically it limits the frame draw rate for the application
        bool enableVSync = false;
        if (enableVSync) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }

        // Here we save a ref to the current window, so we can receive callbacks from GLFW
        // Other solution could be a map which maps GLFWwindow pointer to Window pointer
        glfwSetWindowUserPointer(w, &window);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(w, [](GLFWwindow *window, int width, int height) {
            auto *w = (Window *) glfwGetWindowUserPointer(window);

            Event event = {};
            w->dispatch(event);
        });

        glfwSetWindowCloseCallback(w, [](GLFWwindow *window) {
            auto *w = (Window *) glfwGetWindowUserPointer(window);

            Event event = {};
            event.type = EVENT_WINDOW_CLOSE;
            w->dispatch(event);
        });

        // Keyboard callback
        glfwSetKeyCallback(w, [](GLFWwindow *window, int key, int scancode, int action, int mods) {

            auto *w = (Window *) glfwGetWindowUserPointer(window);

            Event event = {};

            switch (action) {
                case GLFW_PRESS: {

                    Input::UpdateKeyState((KeyCode)key, KeyState::Pressed);
                    w->dispatch(event);

                    break;
                }
                case GLFW_RELEASE: {

                    Input::UpdateKeyState((KeyCode)key, KeyState::Released);
                    w->dispatch(event);

                    break;
                }
                case GLFW_REPEAT: {

                    Input::UpdateKeyState((KeyCode)key, KeyState::Held);
                    w->dispatch(event);

                    break;
                }
            }
        });

        glfwSetCharCallback(w, [](GLFWwindow *window, uint32_t codepoint) {

            auto *w = (Window *) glfwGetWindowUserPointer(window);

            Event event = {};
            w->dispatch(event);
        });

        glfwSetMouseButtonCallback(w, [](GLFWwindow *window, int button, int action, int mods) {

            auto *w = (Window *) glfwGetWindowUserPointer(window);

            Event event = {};


            switch (action) {
                case GLFW_PRESS: {
                    w->dispatch(event);
                    break;
                }
                case GLFW_RELEASE: {
                    w->dispatch(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(w, [](GLFWwindow *window, double xOffset, double yOffset) {

            auto *w = (Window *) glfwGetWindowUserPointer(window);

            Event event = {};
            w->dispatch(event);
        });

        glfwSetCursorPosCallback(w, [](GLFWwindow *window, double x, double y) {

            auto *w = (Window *) glfwGetWindowUserPointer(window);

            Event event = {};
            w->dispatch(event);
        });

        glfwSetWindowIconifyCallback(w, [](GLFWwindow *window, int iconified) {

            auto *w = (Window *) glfwGetWindowUserPointer(window);

            Event event = {};
            w->dispatch(event);
        });

        glfwSetFramebufferSizeCallback(w, [](GLFWwindow *window, int w, int h) {

            auto *wind = (Window *) glfwGetWindowUserPointer(window);

            wind->setBufferSize(w, h);
            glViewport(0, 0, w, h);
        });
    }
}

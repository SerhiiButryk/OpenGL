#include "GLEngine.h"

#include <GL/glew.h>

#include "external/GLFBridge.h"
#include <common/Log.h>

namespace xengine {

    bool GLEngine::initEngine() {

        if (IS_INITIALIZED) {
            return CAN_BE_USED;
        }

        // Init logger lib
        initLogger();

        /* Initializing the GLFW library */
        if (!GLFBridge::init()) {
            logError("Failed to init GLFW library");
            CAN_BE_USED = false;
            return false;
        }

        IS_INITIALIZED = true;
        CAN_BE_USED = true;

        return true;
    }

    void GLEngine::setViewPorts(int bufferWidth, int bufferHeight) {
        /* Setup view ports in OpenGL */
        glViewport(0, 0, bufferWidth, bufferHeight);
    }

    void GLEngine::setBlending(bool enable) {
        if (enable) {
            glEnable(GL_BLEND);
            logInfo("GLEngine::setBlending() Blending enabled");
        } else {
            glDisable(GL_BLEND);
            logInfo("GLEngine::setBlending() Blending disabled");
        }
    }

    void GLEngine::setBlendingMode() {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        logInfo("GLEngine::setBlending() Blending mode is set");
    }

    void GLEngine::printInfo() {
        auto version = glGetString(GL_VERSION);
        if (version != nullptr)
            logInfo("GL version: '{}'", std::string((char*)version));

        auto vendor = glGetString(GL_VENDOR);
        if (vendor != nullptr)
            logInfo("GL vendor: '{}'", std::string((char*)version));

        auto render = glGetString(GL_RENDER);
        if (render != nullptr)
            logInfo("GPU name: '{}'", std::string((char*)version));
    }

    void GLAPIENTRY
    MessageCallback(GLenum source,
                    GLenum type,
                    GLuint id,
                    GLenum severity,
                    GLsizei length,
                    const GLchar *message,
                    const void *userParam)
    {
        if (type == GL_DEBUG_TYPE_ERROR) {
            logError("OpenGL ERROR: {}", message);
        } else {
            logWarn("OpenGL MESSAGE: {}", message);
        }
    }

    void GLEngine::setDebugCallback() {
        const char *versionString = (char *) glGetString(GL_VERSION);
        const std::string string(versionString);

        float version = std::stof(versionString);

        if (version >= 4.5f) {
            logInfo("GLEngine::setDebugCallback() Can set a debug callback. Version = {}", version);
            glDebugMessageCallback(MessageCallback, 0);
        } else {
            // TODO: Implement error handling in this case
            logInfo("GLEngine::setDebugCallback() !!! CANNOT set a debug callback !!! Version = {}", version);
        }
    }

}

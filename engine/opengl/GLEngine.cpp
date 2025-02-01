#include "GLEngine.h"

#include <GL/glew.h>

#include <external/PlatformGateWay.h>
#include <common/Log.h>
#include <common/Diagnostic.h>

namespace xengine {

    bool GLEngine::initEngine() {
        LOG_DEBUG("GLEngine::initEngine()");

        if (IS_INITIALIZED) {
            LOG_DEBUG("GLEngine::initEngine() already initialized");
            return CAN_BE_USED;
        }

        /* Initializing the GLFW library */
        if (!PlatformGateWay::init()) {
            LOG_ERROR("Failed to init GLFW library");
            CAN_BE_USED = false;
            return false;
        }

        IS_INITIALIZED = true;
        CAN_BE_USED = true;

        LOG_DEBUG("GLEngine::initEngine() done");

        return true;
    }

    void GLEngine::setViewPorts(int bufferWidth, int bufferHeight) {
        /* Setup view ports in OpenGL */
        glViewport(0, 0, bufferWidth, bufferHeight);
    }

    void GLEngine::setBlending(bool enable) {
        if (enable) {
            glEnable(GL_BLEND);
            LOG_INFO("GLEngine::setBlending() Blending enabled");
        } else {
            glDisable(GL_BLEND);
            LOG_INFO("GLEngine::setBlending() Blending disabled");
        }
    }

    void GLEngine::setBlendingMode() {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        LOG_INFO("GLEngine::setBlending() Blending mode is set");
    }

    void GLEngine::printInfo() {
        auto version = glGetString(GL_VERSION);
        auto vendor = glGetString(GL_VENDOR);
        auto render = glGetString(GL_RENDERER);

        const char* versionStr = "";
        const char* vendorStr = "";
        const char* renderStr = "";

        if (version != nullptr)
            versionStr = (char*)version;

        if (vendor != nullptr)
            vendorStr = (char*)vendor;

        if (render != nullptr)
            renderStr = (char*)render;

        LOG_INFO("OPENGL: '{}' '{}' '{}'", versionStr, vendorStr, renderStr);
    }

    char* GLEngine::getVersionsInfo() {

        auto version = glGetString(GL_VERSION);
        auto vendor = glGetString(GL_VENDOR);
        auto render = glGetString(GL_RENDERER);

        std::string versionStr = "Versions:\n";

        if (version) {
            versionStr += "OpenGL - ";
            versionStr += (char*)version;
        }

        versionStr += '\n';

        if (vendor) {
            versionStr += "Vendor - ";
            versionStr += (char*)vendor;
        }

        versionStr += '\n';

        if (render) {
            versionStr += "Renderer - ";
            versionStr += (char*)render;
        }

        versionStr += '\n';

        return strdup(versionStr.c_str());
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
            LOG_ERROR("OpenGL ERROR: {}", message);
        } else {
            LOG_WARN("OpenGL MESSAGE: {}", message);
        }
    }

    void GLEngine::setDebugCallback() {
        const char *versionString = (char *) glGetString(GL_VERSION);
        const std::string string(versionString);

        float version = std::stof(versionString);

        if (version >= 4.5f) {
            LOG_INFO("GLEngine::setDebugCallback() Can set a debug callback. Version = {}", version);
            glDebugMessageCallback(MessageCallback, 0);
        } else {
            // TODO: Implement error handling in this case
            LOG_INFO("GLEngine::setDebugCallback() !!! CANNOT set a debug callback !!! Version = {}", version);
            ASSERT(false);
        }
    }

}

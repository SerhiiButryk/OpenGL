#include "GLEngine.h"

#include "external/GLFBridge.h"
#include <common/Log.h>

bool GLEngine::initEngine() {

    /* Initializing the GLFW library */
    if (!GLFBridge::init()) {
        logError("Failed to init GLFW library");
        GLFBridge::cleanup();
        return false;
    }

    return true;
}

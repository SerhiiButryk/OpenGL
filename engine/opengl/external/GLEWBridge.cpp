#include "GLEWBridge.h"

#include <GL/glew.h>
#include <common/Log.h>

bool GLEWBridge::init(bool enableExtensions)
{
    /* Enable modern extension features  */
    if (enableExtensions)
        glewExperimental = GL_TRUE;

    return GLEW_OK == glewInit();
}

void GLEWBridge::setViewPorts(int bufferWidth, int bufferHeight)
{
    /* Setup view ports in OpenGL */

    glViewport(0, 0, bufferWidth, bufferHeight);
}

void GLEWBridge::printInfo()
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

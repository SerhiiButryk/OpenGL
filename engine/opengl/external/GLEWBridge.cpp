#include "GLEWBridge.h"

#include <GL/glew.h>

namespace xengine {

bool GLEWBridge::IS_OPENGL_CAN_BE_USED = false;

bool GLEWBridge::init(bool enableExtensions)
{
    /* Enable modern extension features  */
    if (enableExtensions)
        glewExperimental = GL_TRUE;

    IS_OPENGL_CAN_BE_USED = GLEW_OK == glewInit();

    return IS_OPENGL_CAN_BE_USED;
}

}
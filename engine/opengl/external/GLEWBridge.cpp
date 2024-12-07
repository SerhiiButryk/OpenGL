#include "GLEWBridge.h"

#include <GL/glew.h>

namespace xengine {

    bool GLEWBridge::IS_OPENGL_CAN_BE_USED = false;
    bool GLEWBridge::IS_INITIALIZED = false;

    bool GLEWBridge::init(bool enableExtensions)
    {
        if (IS_INITIALIZED)
            return IS_OPENGL_CAN_BE_USED;

        /* Enable modern extension features  */
        if (enableExtensions)
            glewExperimental = GL_TRUE;

        IS_OPENGL_CAN_BE_USED = GLEW_OK == glewInit();

        IS_INITIALIZED = true;

        return IS_OPENGL_CAN_BE_USED;
    }

}
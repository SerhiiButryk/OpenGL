#include "GLEWBridge.h"

#include <common/Log.h>
#include <GL/glew.h>

namespace xengine {

    bool GLEWBridge::init()
    {
        if (IS_INITIALIZED)
            return IS_OPENGL_CAN_BE_USED;

        /* Enable modern extension features  */
        bool enableExtensions = true;
        if (enableExtensions)
            glewExperimental = GL_TRUE;

        unsigned int result = glewInit();
        IS_OPENGL_CAN_BE_USED = GLEW_OK == result;

        if (GLEW_OK != result)
        {
            LOG_ERROR("GLEW Error: {}", reinterpret_cast<const char *>(glewGetErrorString(result)));
        }

        IS_INITIALIZED = true;

        return IS_OPENGL_CAN_BE_USED;
    }

}
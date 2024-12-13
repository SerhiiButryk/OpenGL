#pragma once

/*
    This is a simple and handy wrapper around GLEW APIs.
    GLEW library provides access to OpenGL APIs.

    Docs: https://glew.sourceforge.net/
*/

namespace xengine {

    class GLEWBridge
    {
    public:
        /* Initializes the GLEW library */
        static bool init();
    private:
        static bool IS_OPENGL_CAN_BE_USED;
        static bool IS_INITIALIZED;
    };

}
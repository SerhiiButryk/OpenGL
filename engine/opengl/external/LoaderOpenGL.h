#pragma once

/*
    This is a simple and handy wrapper around GLEW APIs.
    GLEW library provides access to OpenGL APIs.

    Docs: https://glew.sourceforge.net/
*/

namespace xengine {

    class LoaderOpenGL
    {
    public:
        /* Initializes the GLEW library */
        static bool init();
    private:
        static inline bool IS_OPENGL_CAN_BE_USED = false;
        static inline bool IS_INITIALIZED = false;
    };

}
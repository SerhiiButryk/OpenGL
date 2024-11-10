#pragma once

/*
    This is a simple and handy wrapper around GLEW APIs.
    GLEW library provides access to OpenGL APIs.

    Docs: https://glew.sourceforge.net/
*/

class GLEWBridge
{
public:
    /* Initializes the GLEW library */
    static bool init(bool enableExtensions);
private:
    static bool IS_OPENGL_CAN_BE_USED;
};
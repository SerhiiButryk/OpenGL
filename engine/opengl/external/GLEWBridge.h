#pragma once

/*
    This is a simple and handy wrapper around GLEW APIs.
    GLEW library provides access to OpenGL APIs.
*/

class GLEWBridge
{
public:
    /* Initializes the GLEW library */
    static bool init(bool enableExtensions);

    static void setViewPorts(int bufferWidth, int bufferHeight);

    static void printInfo();
};

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../window/Window.h"

/*
	Entry point for GLF library APIs.
	This is a simple handy wrapper which deals with GLF APIs.
*/

class GLFBridge 
{
public:

	/* Initializes the GLFW library */
	static bool init();
	
	/* Clen up the GLFW library resources */
	static void cleanup();
	
	static bool createWindow(Window& window, const char* title, int width, int height);

	/* Destroyes window */
	static void destroyWindow(const Window& window);
	
};
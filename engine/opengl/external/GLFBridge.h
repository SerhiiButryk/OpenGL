#pragma once

#include "../window/Window.h"

/*
	This is a simple and handy wrapper which deals with GLF APIs.
	GLF library manages creation of windows in our application.

	Docs: https://www.glfw.org/docs/latest/
*/

class GLFBridge 
{
public:

	/* Initializes the GLFW library */
	static bool init();
	
	/* Cleans up the GLFW library resources */
	static void cleanup();

	/* Creates the window */
	static bool createWindow(Window& window, const char* title, int width, int height);

	/* Destroys window */
	static void destroyWindow(const Window& window);
	
};
#pragma once

#include <window/Window.h>

namespace xengine {

/*
	This is a simple and handy wrapper around GLFW APIs.
	GLFW library manages creation of windows in our application
	and platform specific calls

	Docs: https://www.glfw.org/docs/latest/
*/

	class PlatformGateWay
	{
	public:

		/* Initializes the GLFW library */
		static bool init();

		/* Cleans up the GLFW library resources */
		static void cleanup();

		/* Creates the window */
		static bool createWindow(Window& window, const char* title, int width, int height);
		static void initWindowConfigs(Window& window);

		/* Destroys window */
		static void destroyWindow(const Window& window);

	};

}
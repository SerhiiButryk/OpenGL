#include "Window.h"

#include "opengl/external/GLFBridge.h"
#include "common/Log.h"

Window::Window()
{
}

Window::~Window()
{	
}

bool Window::create(const char* title, int width, int height)
{
	if (window != nullptr) {
		logError("Window::create() Window is not null, return");
		return false;
	}

	bool result = GLFBridge::createWindow(*this, title, width, height);

	if (!result) {
		logError("Window::create() Failed to create window");
		return false;
	}

	GLFBridge::initWindowConfigs(*this);

	logInfo("Window::create() Window is created");

	return true;
}

void Window::destroy()
{
	if (window == nullptr) 
	{
		logError("Window::destroy() Window is null, return");
		return;
	}

	GLFBridge::destroyWindow(*this);
	window = nullptr;

	logInfo("Window::destroy() Window is destroyed");
}
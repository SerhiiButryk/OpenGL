#include "Window.h"

#include "../external/GLFBridge.h"

#include "../../common/Log.h"

Window::Window()
{
}

Window::~Window()
{	
}

bool Window::create(const char* title, int width, int height)
{
	if (window != nullptr) 
	{
		logError("Window::create() Window is not null, return");
		return false;
	}

	bool result = GLFBridge::createWindow(*this, title, width, height);

	logInfo("Window::create() Window is created, result = ", result);

	return result;
}

void Window::destroy()
{
	if (window == nullptr) 
	{
		logError("Window::destroy() Error: Window is not valid, return");
		return;
	}

	GLFBridge::destroyWindow(*this);
	window = nullptr;

	logInfo("Window::destroy() Window is destroyed");
}

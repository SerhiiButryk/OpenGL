#include "Window.h"

#include <opengl/external/GLEWBridge.h>

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

	const bool result = GLFBridge::createWindow(*this, title, width, height);

	logInfo("Window::create() Window is created, result = ", result);

	if (!result) {
		return false;
	}

	GLFBridge::initWindowConfigs(*this);

	// TODO: Maybe find another place where to do this
	// At this point we init GLEW
	if (!GLEWBridge::init(true))
		return false;

	setupViewport();

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

void Window::setupViewport() const
{
	GLEWBridge::setViewPorts(bufferWidth, bufferHeight);
}

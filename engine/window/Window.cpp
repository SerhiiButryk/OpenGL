#include "Window.h"

#include "opengl/external/GLFBridge.h"
#include "common/Log.h"

namespace xengine {

	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	bool Window::create(const char* title, int width, int height)
	{
		if (window != nullptr) {
			LOG_ERROR("Window::create() Window is not null, return");
			return false;
		}

		bool result = GLFBridge::createWindow(*this, title, width, height);

		if (!result) {
			LOG_ERROR("Window::create() Failed to create window");
			return false;
		}

		GLFBridge::initWindowConfigs(*this);

		LOG_INFO("Window::create() Window is created");

		return true;
	}

	void Window::destroy()
	{
		if (window == nullptr)
		{
			LOG_ERROR("Window::destroy() Window is null, return");
			return;
		}

		GLFBridge::destroyWindow(*this);
		window = nullptr;

		LOG_INFO("Window::destroy() Window is destroyed");
	}

}
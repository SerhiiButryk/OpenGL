#include "Window.h"

/* Glew is included first because it loads and provides OpenGL APIs */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "opengl/external/GLFBridge.h"
#include "common/Log.h"
#include <MainApplication.h>

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

	void Window::onProcess(void* app) {

		auto* mainApp = static_cast<MainApplication*>(app);

		/*
			 Swap front and back buffers
			 Back buffer is a buffer which user cannot see.
			 Front buffer is a buffer which user sees and which the window is using.
			 We draw to the back buffer, and then we swap the buffer to reflect
			 things on the screen.
		  */

		glfwSwapBuffers((GLFWwindow*) mainApp->getWindow());

		/* Get user or process events */

		glfwPollEvents();
	}

	bool Window::onEvent(const Event &event) {
		return false;
	}

	void Window::dispatch(const Event &event) {

		bool handled = onEvent(event);

		if (handled)
			return;

		if (m_eventListener != nullptr)
			m_eventListener->onEvent(event);
	}
}

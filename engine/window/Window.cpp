#include "Window.h"

/* Glew is included first because it loads and provides OpenGL APIs */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <external/PlatformGateWay.h>
#include <common/Log.h>
#include <app/MainApplication.h>
#include <common/Diagnostic.h>
#include <opengl/GLEngine.h>
#include <opengl/external/LoaderOpenGL.h>

namespace xengine {

	Window::Window()
	{
	}

	Window::~Window()
	{
		// Should be null at this point
		ASSERT(window == nullptr);
	}

	bool Window::create(WindowConfigs configs)
	{
		if (window != nullptr) {
			LOG_ERROR("Window::create() Window is not null, return");
			return false;
		}

		bool result = PlatformGateWay::createWindow(*this, configs.title, configs.width, configs.height);

		if (!result) {
			LOG_ERROR("Window::create() Failed to create window");
			return false;
		}

		// At this point we should make sure that GLEW is initialized
		if (!LoaderOpenGL::init()) {
			LOG_ERROR("Window::create() Failed to init GLEW lib");
			return false;
		}

		GLEngine::setViewPorts(bufferWidth, bufferHeight);

		// Log debug info
		GLEngine::printInfo();
		GLEngine::setDebugCallback();

		// Blending
		GLEngine::setBlending(true);
		GLEngine::setBlendingMode();

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

		PlatformGateWay::destroyWindow(*this);
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

		// Window not handling any events currently

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

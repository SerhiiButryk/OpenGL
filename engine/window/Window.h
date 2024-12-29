#pragma once

#include <internal/MainThreadObserver.h>
#include <window/events/Event.h>
#include <window/events/EventListener.h>

#include "WindowConfigs.h"

/*
	A high level window class which manages a single window in our application
*/

namespace xengine {

	class Window : public EventConsumer, public EventDispatcher, public MainThreadObserver
	{
	public:

		Window();
		~Window() override;

		bool create(WindowConfigs configs);
		void destroy();

		void* getWindow() const { return window; }
		void setWindow(void* window) { this->window = window; }

		void setBufferSize(int width, int height) { this->bufferWidth = width; this->bufferHeight = height; }

		inline int getBufferWidth() const { return this->bufferWidth; }
		inline int getBufferHeight() const { return this->bufferHeight; }

		// Called by main thread
		void onProcess(void* app) override;

		// Events
		bool onEvent(const Event &event) override;
		void dispatch(const Event &event) override;

		void setEventListener(EventListener* eventListener) { m_eventListener = eventListener; }

	private:
		void* window = nullptr;
		int bufferWidth {}, bufferHeight {};
		EventListener* m_eventListener = nullptr;
	};

}


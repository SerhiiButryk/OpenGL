#pragma once

#include <MainThreadObserver.h>
#include <app/Lifecycle.h>
#include <window/events/Event.h>
#include <window/events/EventListener.h>

#include "WindowConfigs.h"

/*
	A high level window class which manages a single window in our application
*/

namespace xengine {

	class Window final : public EventConsumer, public EventDispatcher,
		public MainThreadObserver, public Lifecycle
	{
	public:

		Window();
		~Window() override;

		void onCreate() override;

		void onDestroy() override;

		void onCreateWindow(WindowConfigs windowConfigs);

		void* getWindow() const { return window; }
		void setWindow(void* window) { this->window = window; }

		void setBufferSize(int width, int height) { this->bufferWidth = width; this->bufferHeight = height; }

		int getBufferWidth() const { return this->bufferWidth; }
		int getBufferHeight() const { return this->bufferHeight; }

		// Called by main thread
		void onProcess(void* app) override;

		// Events
		bool onEvent(const Event &event) override;
		void dispatch(const Event &event) override;

		void setEventListener(EventListener* eventListener) { m_eventListener = eventListener; }

	private:
		bool create(WindowConfigs configs);
		void destroy();

	private:
		void* window = nullptr;
		int bufferWidth {}, bufferHeight {};
		EventListener* m_eventListener = nullptr;
	};

}


#pragma once

/*
	A high level window class which manages a single window in our application
*/

namespace xengine {

class Window
{
	public:

		Window();
		~Window();

		bool create(const char* title, int width, int height);
		void destroy();

		void* getWindow() const { return window; }
		void setWindow(void* window) { this->window = window; }

		void setBufferSize(int width, int height) { this->bufferWidth = width; this->bufferHeight = height; }

		inline int getBufferWidth() const { return this->bufferWidth; }
		inline int getBufferHeight() const { return this->bufferHeight; }

	private:
		void* window = nullptr;
		int bufferWidth {}, bufferHeight {};
	};

}


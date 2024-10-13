#pragma once

/*
	Creates and manages application window
*/

class Window
{
public:

	Window();
	~Window();

	bool create(const char* title, int width, int height);

	void destroy();

	void* getWindow() const { return window; }
	void setWindow(void* window) { this->window = window; }

private:
	void* window = nullptr;
};


#pragma once

/* Glew is included first because it loads and provides OpenGL APIs */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window/Window.h"

class Lifecycle {
    public:

    Lifecycle() = default;
    virtual ~Lifecycle() = default;

    virtual void onCreate() {}

    virtual void onDestroy() {}
};

class Application : public Lifecycle {
public:
    Application() = default;
    virtual ~Application() = default;

    void onCreate() override {}
    void onDestroy() override {}
};

/*
 * A class which represents an instance of our application.
 * An application manages only height level states or configurations, like a window.
 */
class MainApplication : public Application {
public:
    MainApplication();
    virtual ~MainApplication();

    void onCreateWindow() const;
    void onCreate() override;
    void onDestroy() override;

    inline GLFWwindow* getWindow() const { return (GLFWwindow*) m_parentWindow->getWindow(); }
    inline void setClientApplication(Application* app) { m_clientApp = app; }

private:
    Window* m_parentWindow = nullptr;
    Application* m_clientApp = nullptr;
};

#pragma once

/* Glew is included first because it loads and provides OpenGL APIs */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "MainThread.h"
#include "window/Window.h"
#include "Internal.h"

namespace xengine {

    /*
     * A class which represents an instance of our application.
     * An application manages only height level states or configurations, like a window.
     */
    class MainApplication : public InternalApplication {
    public:
        MainApplication();
        virtual ~MainApplication();

        void onCreateWindow() const;

        void onCreate() override;
        void onDestroy() override;

        inline GLFWwindow* getWindow() const { return (GLFWwindow*) m_parentWindow->getWindow(); }

        inline void setClientApplication(Application* app) { m_clientApp = app; }
        inline Application* getClientApplication() const { return m_clientApp; }

        void initConfigs(MainThread* mainThread);

        inline UI* getClientUI() const { return m_clientUI; }

    private:
        Window* m_parentWindow = nullptr;
        Application* m_clientApp = nullptr;
        UI* m_clientUI = nullptr;
    };

}

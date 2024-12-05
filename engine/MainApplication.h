#pragma once

/* Glew is included first because it loads and provides OpenGL APIs */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "MainThread.h"
#include "internal/Application.h"

namespace xengine {

    /*
     * A class which represents an instance of our application.
     * An application manages only high level states or configurations, like a window.
     */
    class MainApplication : public InternalApplication {
    public:
        MainApplication();
        ~MainApplication() override;

        void onCreateWindow() const;

        void onCreate() override;
        void onDestroy() override;

        inline void setClientApplication(Application* app) { m_clientApp = app; }
        inline Application* getClientApplication() const { return m_clientApp; }

        void initConfigs(MainThread* mainThread);

        inline UI* getClientUI() const { return m_clientUI; }
        inline void setClientUI(UI* clientUI) {  m_clientUI = clientUI; }

#ifdef UNIT_TESTS
        void* getParentWindowForTest() const { return m_parentWindow; }
#endif

    private:
        Application* m_clientApp = nullptr;
        UI* m_clientUI = nullptr;
    };

}

#include "MainApplication.h"

#include <common/Log.h>
#include <opengl/GLEngine.h>
#include <opengl/external/GLEWBridge.h>
#include <ui/AppUI.h>

#include "common/Exception.h"

namespace xengine {

    MainApplication::MainApplication() : m_appUI(new ApplicationUI()) {
        LOG_INFO("MainApplication::MainApplication() created");
    }

    MainApplication::~MainApplication() {

        if (m_clientApp != nullptr) {
            delete m_clientApp;
        }

        delete m_appUI;

        LOG_INFO("MainApplication::~MainApplication() destroyed");
    }

    void MainApplication::onCreate() {
        if (m_clientApp != nullptr) {
            m_clientApp->onCreate();
        }

        onCreateWindow();

        m_parentWindow->setEventListener(this);

        LOG_INFO("MainApplication::onCreate");
    }

    void MainApplication::onDestroy() {
        /* Release resources */
        m_parentWindow->destroy();

        // Release client app resources
        if (m_clientApp != nullptr) {
            m_clientApp->onDestroy();
        }

        LOG_INFO("MainApplication::onDestroy");
    }

    void MainApplication::onCreateWindow() const {

        LOG_INFO("MainApplication::onCreateWindow()");

        /* Create a window and its OpenGL context */

        // 3 x 2 aspect ratio
        int width = 1200;
        int height = 800;
        const char* title = "Application";

        if (!m_parentWindow->create(title, width, height)) {
            throwApplicationInitException(ApplicationInitException::WINDOW_CREATION_ERROR);
        }

        // At this point we should make sure that GLEW is initialized
        if (!GLEWBridge::init()) {
            LOG_ERROR("MainApplication::onCreateWindow Failed to init GLEW lib");
            throwApplicationInitException(ApplicationInitException::LIB_INIT_ERROR);
        }

        GLEngine::setViewPorts(m_parentWindow->getBufferWidth(), m_parentWindow->getBufferHeight());

        // Log debug info
        GLEngine::printInfo();
        GLEngine::setDebugCallback();

        // Blending
        GLEngine::setBlending(true);
        GLEngine::setBlendingMode();
    }

    void MainApplication::attachThread(MainThread* mainThread) {
        m_main_thread = mainThread;
        mainThread->addThreadObserver(m_parentWindow);
        mainThread->addThreadObserver(m_appUI);
        mainThread->addThreadObserver(this);
        LOG_INFO("MainApplication::attachThread()");
    }

    bool MainApplication::onEvent(const Event &event) {

        if (event.type == EVENT_WINDOW_CLOSE)
            m_main_thread->quit();

        // handled
        return true;
    }
}

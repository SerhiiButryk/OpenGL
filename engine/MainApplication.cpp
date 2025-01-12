#include "MainApplication.h"

#include <common/Log.h>
#include <ui/AppUI.h>

#include "common/Exception.h"

namespace xengine {

    MainApplication::MainApplication() : m_appUI(new ApplicationUI()) {
        LOG_INFO("MainApplication::MainApplication() created");
    }

    MainApplication::~MainApplication() {
        delete m_clientApp;
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

        WindowConfigs windowConfigs = m_clientApp->onCreateWindow();

        if (!m_parentWindow->create(windowConfigs)) {
            throwApplicationInitException(ApplicationInitException::WINDOW_CREATION_ERROR);
        }
    }

    void MainApplication::attachThread(MainThread* mainThread) {
        m_main_thread = mainThread;
        m_appUI->setClientApp(m_clientApp);

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

#include "MainApplication.h"

#include <common/Log.h>
#include <ui/AppUI.h>
#include <common/Timestamp.h>
#include <GLFW/glfw3.h>
#include <common/Exception.h>

static float m_LastTime = 0.0f;

namespace xengine {

    MainApplication::MainApplication() : m_appUI(new ApplicationUI()) {
        LOG_INFO("MainApplication::MainApplication() created");
    }

    MainApplication::~MainApplication() {
        LOG_INFO("MainApplication::~MainApplication() destroyed");
        delete m_clientApp;
        delete m_appUI;
    }

    // Called from main thread

    void MainApplication::onCreate() {
        LOG_INFO("MainApplication::onCreate");

        if (m_clientApp != nullptr) {
            m_clientApp->onCreate();
        }

        m_parentWindow->onCreate();

        onCreateWindow();

        m_parentWindow->setEventListener(this);

        m_appUI->onCreate();

    }

    // Called from main thread

    void MainApplication::onDestroy() {
        LOG_INFO("MainApplication::onDestroy");

        m_parentWindow->onDestroy();

        m_appUI->onDestroy();

        /* Release resources */
        m_parentWindow->destroy();

        // Release client app resources
        if (m_clientApp != nullptr) {
            m_clientApp->onDestroy();
        }

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
        LOG_INFO("MainApplication::attachThread()");
        m_main_thread = mainThread;

        // We register only one observer
        // Application will get callbacks from main thread and will call other components
        mainThread->addThreadObserver(this);
    }

    bool MainApplication::onEvent(const Event &event) {

        if (event.type == EVENT_WINDOW_CLOSE)
            m_main_thread->quit();

        // handled
        return true;
    }

    ////////////////////////////// Callback from main thread ///////////////////////////////////

    void MainApplication::onStart() {

        m_parentWindow->onStart();

        m_appUI->onStart();

    }

    // This is called from main thread per frame

    void MainApplication::onProcess(void *app) {

        // Calculate frame update time
        // TODO: Abstract glfw call
        auto systemCurrentTime = (float) glfwGetTime();
        Timestamp deltaTime = systemCurrentTime - m_LastTime;
        m_LastTime = systemCurrentTime;
        ((InternalApplication*) app)->setFrameDeltaTime(deltaTime);

        m_appUI->onProcess(app);

        m_parentWindow->onProcess(app);

    }

    void MainApplication::onEnd() {

        m_parentWindow->onEnd();

        m_appUI->onEnd();

    }

    ////////////////////////////////////////////////////////////////////////////////////////////
}

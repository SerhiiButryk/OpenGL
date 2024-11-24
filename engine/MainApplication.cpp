#include "MainApplication.h"

#include <common/Log.h>
#include <opengl/GLEngine.h>
#include <opengl/external/GLEWBridge.h>
#include <ui/AppUI.h>

#include "common/Exception.h"
#include "opengl/Shader.h"

namespace xengine {

    MainApplication::MainApplication() {
        logInfo("MainApplication::MainApplication() created");
    }

    MainApplication::~MainApplication() {

        delete m_parentWindow;

        if (m_clientApp != nullptr) {
            delete m_clientApp;
        }

        if (m_clientUI != nullptr) {
            delete m_clientUI;
        }

        logInfo("MainApplication::~MainApplication() destroyed");
    }

    void MainApplication::onCreate() {
        if (m_clientApp != nullptr) {
            m_clientApp->onCreate();
        }
        logInfo("MainApplication::onCreate");
    }

    void MainApplication::onDestroy() {
        /* Release resources */
        m_parentWindow->destroy();

        // Release client app resources
        if (m_clientApp != nullptr) {
            m_clientApp->onDestroy();
        }

        logInfo("MainApplication::onDestroy");
    }

    void MainApplication::onCreateWindow() const {

        logInfo("MainApplication::onCreateWindow()");

        /* Create a window and its OpenGL context */

        // 3 x 2 aspect ratio
        int width = 1200;
        int height = 800;
        const char* title = "Application";

        if (!m_parentWindow->create(title, width, height)) {
            throwApplicationInitException(ApplicationInitException::WINDOW_CREATION_ERROR);
        }

        // At this point we init GLEW
        if (!GLEWBridge::init(true)) {
            logError("MainApplication::onCreateWindow Failed to init GLEW lib");
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

    void MainApplication::initConfigs(MainThread* mainThread) {
        mainThread->addThreadObserver(new AppUI(m_clientUI));
        logInfo("MainApplication::initConfigs() added UI component");
    }

}
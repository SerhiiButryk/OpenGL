#include "Application.h"

#include <common/Log.h>
#include <opengl/GLEngine.h>
#include <opengl/external/GLEWBridge.h>
#include "common/Exception.h"
#include "opengl/Shader.h"

MainApplication::MainApplication(): m_parentWindow(new Window()) {
    logInfo("MainApplication::Application() created");
}

MainApplication::~MainApplication() {

    delete m_parentWindow;

    if (m_clientApp != nullptr) {
        delete m_clientApp;
    }

    logInfo("MainApplication::~Application() destroyed");
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
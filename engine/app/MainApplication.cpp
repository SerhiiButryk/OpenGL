#include "MainApplication.h"

#include <common/Log.h>
#include <common/Timestamp.h>
#include <GLFW/glfw3.h>
#include <common/Exception.h>

namespace xengine {

    MainApplication::MainApplication() {
        LOG_INFO("MainApplication::MainApplication() created");
        m_decoratorUI = new DecoratorUI(m_parentWindow);
        // Push our decorator layer
        pushLayer(m_decoratorUI);
    }

    MainApplication::~MainApplication() {
        LOG_INFO("MainApplication::~MainApplication() destroyed");
        delete m_clientApp;

        // Detach layer objects
        for (const auto & it : m_layerStack) {
            it->onDetach();
            delete it;
        }
    }

    // Called from main thread

    void MainApplication::onCreate() {
        LOG_INFO("MainApplication::onCreate");

        if (m_clientApp != nullptr) {
            m_clientApp->onCreate();
        }

        m_parentWindow->onCreate();

        /* Create a window and its OpenGL context */

        WindowConfigs windowConfigs = m_clientApp->onCreateWindow();

        m_parentWindow->onCreateWindow(windowConfigs);

        m_parentWindow->setEventListener(this);
    }

    // Called from main thread

    void MainApplication::onDestroy() {
        LOG_INFO("MainApplication::onDestroy");

        m_parentWindow->onDestroy();

        // Release client app resources
        if (m_clientApp != nullptr) {
            m_clientApp->onDestroy();
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

        for (const auto & it : m_layerStack) {
            if (it->onEvent(event)) {
                // Break and stop propagating the event
                return true;
            }
        }

        // handled
        return false;
    }

    ////////////////////////////// Callback from main thread ///////////////////////////////////

    void MainApplication::onStart() {

        m_parentWindow->onStart();

        for (const auto & it : m_layerStack) {
            it->onAttach();
        }

    }

    // This is called from main thread per frame

    void MainApplication::onProcess(void *app) {

        static float lastTime = 0.0f;

        // Calculate frame update time
        // TODO: Abstract glfw call !!!
        auto systemCurrentTime = (float) glfwGetTime();
        Timestamp deltaTime = systemCurrentTime - lastTime;
        lastTime = systemCurrentTime;
        ((InternalApplication*) app)->setFrameDeltaTime(deltaTime);

        for (const auto & it : m_layerStack) {
            it->onDraw();
        }

        m_parentWindow->onProcess(app);

    }

    void MainApplication::onEnd() {

        m_parentWindow->onEnd();

    }

    ////////////////////////////////////////////////////////////////////////////////////////////

    void MainApplication::pushLayer(Layer *layer) {
        m_layerStack.pushLayer(layer);
    }

    void MainApplication::popLayer(Layer *layer) {
        m_layerStack.popLayer(layer);
        layer->onDetach();
    }

    void MainApplication::pushOverLayer(Layer *layer) {
        m_layerStack.pushOverlay(layer);
    }

    void MainApplication::popOverLayer(Layer *layer) {
        m_layerStack.popOverlay(layer);
        layer->onDetach();
    }
}

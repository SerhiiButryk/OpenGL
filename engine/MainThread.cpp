#include "MainThread.h"

#include <MainApplication.h>
#include <common/Log.h>
#include <opengl/GLEngine.h>
#include <opengl/external/GLFBridge.h>
#include "common/Exception.h"

namespace xengine {

    void MainThread::onCreate() {
        logInfo("MainThread::onCreate");

        // Initialize
        if (!GLEngine::initEngine()) {
            throwApplicationInitException(ApplicationInitException::WINDOW_CREATION_ERROR);
        }

        // Initialize components
        for (auto&& ob : m_observers) {
            ob->onCreate();
        }
    }

    void MainThread::onDestroy() {
        logInfo("MainThread::onDestroy");

        // Clean up
        for (auto&& ob : m_observers) {
            ob->onDestroy();
        }

        // Clean up our engine
        GLFBridge::cleanup();

        // Remove observers
        for (auto&& ob : m_observers) {
            delete ob;
        }

        m_observers.clear();
    }

    void MainThread::loop(InternalApplication* app) {

        auto* mainApp = dynamic_cast<MainApplication*>(app);

        // Create our UI
        for (auto&& ob : m_observers) {
            ob->onBeforeProcess();
        }

        /* Loop until the user closes the window */

        while (!glfwWindowShouldClose((GLFWwindow*) mainApp->getWindow()))
        {

            // Render our UI
            for (auto&& ob : m_observers) {
                ob->onProcess();
            }

            /*
               Swap front and back buffers
               Back buffer is a buffer which user cannot see.
               Front buffer is a buffer which user sees and which the window is using.
               We draw to the back buffer, and then we swap the buffer to reflect
               things on the screen.
            */

            glfwSwapBuffers((GLFWwindow*) mainApp->getWindow());

            /* Get user or process events */

            glfwPollEvents();
        }

        // Destroy our UI
        for (auto&& ob : m_observers) {
            ob->onProcessEnd();
        }

    }

    void MainThread::addThreadObserver(MainThreadObserver* observer) {
        m_observers.push_back(observer);
    }

    void MainThread::removeThreadObserver(MainThreadObserver* observer) {
        for (const auto it = m_observers.begin(); it != m_observers.end();)
        {
            if (*it == observer) {
                logInfo("MainThread::removeThreadObserver removing {:p}", fmt::ptr(*it));
                m_observers.erase(it);
            }
        }
    }

}

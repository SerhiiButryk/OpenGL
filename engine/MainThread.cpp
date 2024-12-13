#include "MainThread.h"

#include <MainApplication.h>
#include <common/Log.h>
#include <opengl/external/GLFBridge.h>

namespace xengine {

    void MainThread::onCreate() {
        logInfo("MainThread::onCreate");

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

        // Remove observers
        for (auto&& ob : m_observers) {
            delete ob;
        }

        m_observers.clear();
    }

    void MainThread::loop(InternalApplication* app) {

        auto* mainApp = dynamic_cast<MainApplication*>(app);

        for (auto&& ob : m_observers) {
            ob->onBeforeProcess();
        }

        /* Loop until the user closes the window */

        while (!glfwWindowShouldClose((GLFWwindow*) mainApp->getWindow()))
        {

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

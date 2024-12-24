#include "MainThread.h"

#include <MainApplication.h>
#include <common/Log.h>

namespace xengine {

    void MainThread::onCreate() {
        LOG_INFO("MainThread::onCreate");

        // Initialize components
        for (auto&& ob : m_observers) {
            ob->onCreate();
        }
    }

    void MainThread::onDestroy() {
        LOG_INFO("MainThread::onDestroy");

        // Clean up
        for (auto&& ob : m_observers) {
            ob->onDestroy();
        }

        m_observers.clear();
    }

    void MainThread::loop(InternalApplication* app) {

        for (auto&& ob : m_observers) {
            ob->onStart();
        }

        /* Loop until we are not stopped */

        while (!m_stop) {
            // We go in reverse oder here.
            // Makes sense when we want to execute code in reverse oder so the first would be the last.
            // So we can run post action like swap buffers or get user event at the end of this loop.
            for (auto riter = m_observers.rbegin(); riter != m_observers.rend(); ++riter) {
                (*riter)->onProcess(app);
            }
        }

        for (auto&& ob : m_observers) {
            ob->onEnd();
        }

    }

    void MainThread::addThreadObserver(MainThreadObserver* observer) {
        m_observers.push_back(observer);
    }

    void MainThread::removeThreadObserver(MainThreadObserver* observer) {
        for (const auto it = m_observers.begin(); it != m_observers.end();)
        {
            if (*it == observer) {
                LOG_DEBUG("MainThread::removeThreadObserver removing {:p}", fmt::ptr(*it));
                m_observers.erase(it);
            }
        }
    }

}

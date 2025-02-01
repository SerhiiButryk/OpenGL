#include "MainThread.h"

#include <app/MainApplication.h>
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

        /* Loop until we are stopped */

        while (!m_stop) {
            for (auto & m_observer : m_observers) {
                m_observer->onProcess(app);
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

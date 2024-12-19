#include "MemoryLeakTest.h"

#include <MainApplication.h>
#include <common/Log.h>
#include <opengl/GLEngine.h>
#include <unit_tests/base/Assert.h>

namespace test {

    /**
     * This test checks that we properly delete objects in classes:
     * MainApplication
     * MainThread
     * Window
     */
    int MemoryLeakTest::run() const {
        LOG_INFO("MemoryLeakTest::run Started");

        using namespace xengine;

        {
            m_memoryTracker->setTrack(false);

            auto* mainApp = new MainApplication();

            // Preconditions
            ASSERT(mainApp->getClientApplication() == 0);
            ASSERT(mainApp->getClientUI() == 0);

            mainApp->setClientApplication(new Application());
            mainApp->setClientUI(new UI());

            void* p1 = mainApp->getClientApplication();
            void* p2 = mainApp->getClientUI();
            void* p3 = mainApp->getParentWindowForTest();

            m_memoryTracker->setTrack(true);

            delete mainApp;

            bool res = m_memoryTracker->checkIfDeallocated(p1);
            ASSERT_LOG(res, "MemoryLeakTest::run possible leak with client application object");

            res = m_memoryTracker->checkIfDeallocated(p2);
            ASSERT_LOG(res, "MemoryLeakTest::run possible leak with client UI object");

            res = m_memoryTracker->checkIfDeallocated(p3);
            ASSERT_LOG(res, "MemoryLeakTest::run possible leak with window object");
        }

        m_memoryTracker->clear();

        {
            m_memoryTracker->setTrack(false);

            auto* mainThread = new MainThread();

            // Preconditions
            ASSERT(mainThread->checkEmptyListForTest());

            mainThread->addThreadObserver(new MainThreadObserver());

            void* p = mainThread->getObserverForTest();

            m_memoryTracker->setTrack(true);

            mainThread->onDestroy();
            delete mainThread;

            bool res = m_memoryTracker->checkIfDeallocated(p);
            ASSERT_LOG(res, "MemoryLeakTest::run possible leak with observer object");
        }

        m_memoryTracker->clear();

        {
            m_memoryTracker->setTrack(false);

            auto* window = new Window();

            // Preconditions
            ASSERT_LOG(GLEngine::initEngine(), "MemoryLeakTest::run failed to init engine");
            ASSERT_LOG(window->getWindow() == 0, "MemoryLeakTest::run window is not null");

            window->create("Test", 100, 100);

            ASSERT_LOG(window->getWindow() != 0, "MemoryLeakTest::run window is not created");

            window->destroy();

            ASSERT_LOG(window->getWindow() == 0, "MemoryLeakTest::run window is not destroyed");

            delete window;
        }

        m_memoryTracker->clear();
        m_memoryTracker->setTrack(false);

        return 0;
    }

}
#include "MemoryLeakTest.h"

#include <MainApplication.h>
#include <common/Log.h>
#include <opengl/GLEngine.h>
#include <unit_tests/base/Assert.h>

namespace test {

    int MemoryLeakTest::run() const {
        logInfo("MemoryLeakTest::run");

        using namespace xengine;

        {
            m_memoryTracker->setTrack(false);

            auto* mainApp = new MainApplication();

            // Preconditions
            ASSERT_TRUE(mainApp->getClientApplication() == 0);
            ASSERT_TRUE(mainApp->getClientUI() == 0);

            mainApp->setClientApplication(new Application());
            mainApp->setClientUI(new UI());

            void* p1 = mainApp->getClientApplication();
            void* p2 = mainApp->getClientUI();
            void* p3 = mainApp->getParentWindowForTest();

            m_memoryTracker->setTrack(true);

            delete mainApp;

            bool res = m_memoryTracker->checkIfDeallocated(p1);
            ASSERT(res, "MemoryLeakTest::run possible leak with client application object");

            res = m_memoryTracker->checkIfDeallocated(p2);
            ASSERT(res, "MemoryLeakTest::run possible leak with client UI object");

            res = m_memoryTracker->checkIfDeallocated(p3);
            ASSERT(res, "MemoryLeakTest::run possible leak with window object");
        }

        m_memoryTracker->clear();

        {
            m_memoryTracker->setTrack(false);

            auto* mainThread = new MainThread();

            // Preconditions
            ASSERT_TRUE(mainThread->checkEmptyListForTest());

            mainThread->addThreadObserver(new MainThreadObserver());

            void* p = mainThread->getObserverForTest();

            m_memoryTracker->setTrack(true);

            mainThread->onDestroy();
            delete mainThread;

            bool res = m_memoryTracker->checkIfDeallocated(p);
            ASSERT(res, "MemoryLeakTest::run possible leak with observer object");
        }

        m_memoryTracker->clear();

        {
            m_memoryTracker->setTrack(false);

            auto* window = new Window();

            // Preconditions
            ASSERT(GLEngine::initEngine(), "MemoryLeakTest::run failed to init engine");
            ASSERT(window->getWindow() == 0, "MemoryLeakTest::run window is not null");

            window->create("Test", 100, 100);

            ASSERT(window->getWindow() != 0, "MemoryLeakTest::run window is not created");

            window->destroy();

            ASSERT(window->getWindow() == 0, "MemoryLeakTest::run window is not destroyed");

            delete window;
        }

        m_memoryTracker->clear();
        m_memoryTracker->setTrack(false);

        return 0;
    }

}
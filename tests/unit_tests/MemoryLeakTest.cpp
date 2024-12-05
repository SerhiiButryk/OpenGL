#include "MemoryLeakTest.h"

#include <MainApplication.h>
#include <common/Log.h>
#include <unit_tests/base/Assert.h>

namespace test {

    int MemoryLeakTest::run() const {
        logInfo("MemoryLeakTest::run");

        using namespace xengine;

        m_memoryTracker->setTrack(true);

        {
            auto* mainApp = new MainApplication();
            mainApp->setClientApplication(new Application());
            mainApp->setClientUI(new UI());

            void* p1 = mainApp->getClientApplication();
            void* p2 = mainApp->getClientUI();
            void* p3 = mainApp->getParentWindowForTest();

            delete mainApp;

            bool res = m_memoryTracker->checkIfDeallocated(p1);
            Assert(res, "MemoryLeakTest::run possible leak with client application object");

            res = m_memoryTracker->checkIfDeallocated(p2);
            Assert(res, "MemoryLeakTest::run possible leak with client UI object");

            res = m_memoryTracker->checkIfDeallocated(p3);
            Assert(res, "MemoryLeakTest::run possible leak with window object");
        }

        m_memoryTracker->clear();

        {
            auto* mainThread = new MainThread();

            mainThread->addThreadObserver(new MainThreadObserver());

            void* p = mainThread->getObserverForTest();

            mainThread->onDestroy();
            delete mainThread;

            bool res = m_memoryTracker->checkIfDeallocated(p);
            Assert(res, "MemoryLeakTest::run possible leak with observer object");
        }

        m_memoryTracker->clear();

        {
            // TODO: Fix
            // auto* window = new Window();
            //
            // window->create("Test", 100, 100);
            // window->destroy();
            //
            // void* p = window->getWindow();
            //
            // delete window;
            //
            // bool res = m_memoryTracker->checkIfDeallocated(p);
            // Assert(res, "MemoryLeakTest::run possible leak with observer object");
        }

        m_memoryTracker->setTrack(false);
        m_memoryTracker->clear();

        return 0;
    }

}
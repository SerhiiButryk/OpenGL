#include "BasicTest.h"

#include <MainApplication.h>
#include <common/Log.h>
#include <opengl/GLEngine.h>
#include <base/Assert.h>

#include <mutex>
#include <condition_variable>
#include <thread>

static std::mutex m;
static std::condition_variable cv;
static bool stopped = false;

namespace test {

    class ThreadObserverForTest : public xengine::MainThreadObserver {
    public:

        virtual void onStart() { startCalled = true; }
        virtual void onProcess(void* app) {}
        virtual void onEnd() { endCalled = true; }

        void onCreate() override { createCalled = true; }
        void onDestroy() override { destroyCalled = true; }

        bool createCalled = false;
        bool destroyCalled = false;
        bool startCalled = false;
        bool endCalled = false;
    };

    /**
     * This test checks that we properly delete objects in classes:
     * MainApplication
     * MainThread
     * Window
     */
    int BasicTest::run() const {
        LOG_INFO("BasicTest::run Started");

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
            ASSERT_LOG(res, "BasicTest::run possible leak with client application object");

            res = m_memoryTracker->checkIfDeallocated(p2);
            ASSERT_LOG(res, "BasicTest::run possible leak with client UI object");

            res = m_memoryTracker->checkIfDeallocated(p3);
            ASSERT_LOG(res, "BasicTest::run possible leak with window object");
        }

        m_memoryTracker->clear();

        {
            m_memoryTracker->setTrack(false);

            auto mainThread = MainThread();

            // Preconditions
            ASSERT(mainThread.checkEmptyListForTest());

            auto ob = ThreadObserverForTest();

            mainThread.addThreadObserver(&ob);

            mainThread.onCreate();
            ASSERT(ob.createCalled);

            std::thread thread([&]() {
                LOG_INFO("BasicTest::run thread started");

                mainThread.loop(nullptr);

                std::unique_lock lock(m);
                stopped = true;
                cv.notify_all();

                LOG_INFO("BasicTest::run thread ended");
            });

            thread.detach();

            LOG_INFO("BasicTest::run try to quit thread");
            mainThread.quit();

            std::unique_lock lock(m);
            if (!stopped) {
                LOG_INFO("BasicTest::run wait for thread to quit");
                cv.wait_for(lock, std::chrono::milliseconds(100));
            }

            ASSERT_LOG(stopped, "BasicTest::run failed to quit thread");

            ASSERT(ob.startCalled);
            ASSERT(ob.endCalled);

            mainThread.onDestroy();
            ASSERT(ob.destroyCalled);

            // After deletion
            ASSERT(mainThread.checkEmptyListForTest());

        }

        m_memoryTracker->clear();

        {
            m_memoryTracker->setTrack(false);

            auto window = Window();

            // Preconditions
            ASSERT_LOG(GLEngine::initEngine(), "BasicTest::run failed to init engine");
            ASSERT_LOG(window.getWindow() == 0, "BasicTest::run window is not null");

            window.create("Test", 100, 100);

            ASSERT_LOG(window.getWindow() != 0, "BasicTest::run window is not created");

            window.destroy();

            ASSERT_LOG(window.getWindow() == 0, "BasicTest::run window is not destroyed");
        }

        m_memoryTracker->clear();
        m_memoryTracker->setTrack(false);

        return 0;
    }

}
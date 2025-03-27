#include "BasicTest.h"

#include <app/MainApplication.h>
#include <common/Log.h>
#include <opengl/GLEngine.h>
#include <base/Assert.h>
#include <ui/UIComponent.h>

#include <mutex>
#include <condition_variable>
#include <thread>

static std::mutex m;
static std::condition_variable cv;
static bool stopped = false;

namespace test {

    class TestThreadObserver : public xengine::MainThreadObserver {
    public:
        void onStart() override { startCalled = true; }
        void onProcess(void* app) override { onProcessCalled = true; }
        void onEnd() override { endCalled = true; }

        bool startCalled = false;
        bool endCalled = false;
        bool onProcessCalled = false;
    };

    class TestUI : public xengine::UIComponent {
    public:
        void onDraw() override {

        }
    };

    class TestApp : public xengine::Application {
    public:

        void onCreate() override {
            pushLayer(new TestUI());
        }

        void onDestroy() override {}

        xengine::WindowConfigs onCreateWindow() override { return {100, 100, "Test"}; }
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

            ASSERT_LOG(GLEngine::initEngine(), "BasicTest::run failed to init engine");

            auto testApp = new TestApp();
            testApp->setDelegate(mainApp);

            mainApp->setClientApplication(testApp);
            mainApp->onCreate();

            void* p1 = mainApp->getClientApplication();
            void* p2 = mainApp->getParentWindowForTest();

            m_memoryTracker->setTrack(true);

            mainApp->onDestroy();

            delete mainApp;

            bool res = m_memoryTracker->checkIfDeallocated(p1);
            ASSERT_LOG(res, "BasicTest::run possible leak with client application object");

            res = m_memoryTracker->checkIfDeallocated(p2);
            ASSERT_LOG(res, "BasicTest::run possible leak with window object");
        }

        m_memoryTracker->clear();

        {
            m_memoryTracker->setTrack(false);

            auto mainThread = MainThread();

            // Preconditions
            ASSERT(mainThread.checkEmptyListForTest());

            auto ob = TestThreadObserver();

            mainThread.addThreadObserver(&ob);

            mainThread.onCreate();

            std::thread thread([&]() {
                LOG_INFO("BasicTest::run thread started");

                mainThread.loop(nullptr);

                std::unique_lock lock(m);
                stopped = true;
                cv.notify_all();

                LOG_INFO("BasicTest::run thread ended");
            });

            thread.detach();

            // Give sometime for main thread to run
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1000ms);

            LOG_INFO("BasicTest::run try to quit thread");
            mainThread.quit();

            std::unique_lock lock(m);
            if (!stopped) {
                LOG_INFO("BasicTest::run wait for thread to quit");
                cv.wait_for(lock, std::chrono::milliseconds(10 * 1000));
            }

            ASSERT_LOG(stopped, "BasicTest::run failed to quit thread");

            ASSERT(ob.startCalled);
            ASSERT(ob.endCalled);
            ASSERT(ob.onProcessCalled);

            mainThread.onDestroy();

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

            WindowConfigs windowConfigs = {100, 100, "Test"};
            window.onCreateWindow(windowConfigs);

            ASSERT_LOG(window.getWindow() != 0, "BasicTest::run window is not created");

            window.onDestroy();

            ASSERT_LOG(window.getWindow() == 0, "BasicTest::run window is not destroyed");
        }

        m_memoryTracker->clear();
        m_memoryTracker->setTrack(false);

        return 0;
    }

}
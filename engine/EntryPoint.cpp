#include <opengl/GLEngine.h>
#include <external/PlatformGateWay.h>

#include <common/Log.h>
#include <app/MainApplication.h>
#include <MainThread.h>
#include <common/Exception.h>

///////////////////////////////////////////////////////////////////
///////////// ENTRY POINT /////////////////////////////////////////
///////////////////////////////////////////////////////////////////

/**
 *  Should be implemented by client
 */
extern xengine::Application* createApplication();

int main()
{
    using namespace xengine;

    int retCode = 0;

    auto* app = new MainApplication();
    auto* mainThread = new MainThread();

    try {

        // Initialize
        if (!GLEngine::initEngine()) {
            throwApplicationInitException(ApplicationInitException::LIB_INIT_ERROR);
        }

        auto* client = createApplication();
        client->setDelegate(app);

        app->setClientApplication(client);

        app->attachThread(mainThread);

        mainThread->onCreate();

        mainThread->loop(app);

    } catch (const ApplicationInitException& e) {
        LOG_ERROR("Received an error: {} {}", e.code, e.what());
        retCode = 1;
    }

    // Release resources either if we got an exception
    // or the program has been closed
    mainThread->onDestroy();

    delete app;
    delete mainThread;

    // Clean up platform resources
    PlatformGateWay::cleanup();

    LOG_INFO("Finished with code {}", retCode);

    return retCode;
}
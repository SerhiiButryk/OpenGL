#include <opengl/GLEngine.h>
#include <opengl/external/GLFBridge.h>

#include "common/Log.h"
#include "MainApplication.h"
#include "MainThread.h"
#include "common/Exception.h"

///////////////////////////////////////////////////////////////////
///////////// MAIN ENTRY POINT OF OUR PROGRAM //////////////////////
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
            throwApplicationInitException(ApplicationInitException::WINDOW_CREATION_ERROR);
        }

        auto* client = createApplication();
        client->setMainApplication(app);

        app->setClientApplication(client);

        auto* clientUi = client->createUI();
        app->setClientUI(clientUi);

        mainThread->onCreate();

        // Will add UI component
        app->initConfigs(mainThread);

        app->onCreate();
        app->onCreateWindow();

        mainThread->loop(app);

    } catch (const ApplicationInitException& e) {
        logError("Received an error: {} {}", e.code, e.what());
        retCode = 1;
    }

    // Release resources either if we got an error
    // or the program has been closed
    mainThread->onDestroy();
    app->onDestroy();

    delete app;
    delete mainThread;

    // Clean up our engine
    GLFBridge::cleanup();

    logInfo("Finished with code {}", retCode);

    return retCode;
}
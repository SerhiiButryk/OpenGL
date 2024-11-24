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
xengine::Application* createApplication();

int main()
{
    using namespace xengine;

    int retCode = 0;

    auto* app = new MainApplication();
    auto* mainThread = new MainThread();

    try {

        auto* client = createApplication();
        client->setMainApplication(app);

        app->setClientApplication(client);

        auto* clientUi = client->createUI();
        app->setClientUI(clientUi);

        mainThread->onCreate();

        // Add UI component
        app->initConfigs(mainThread);

        app->onCreate();
        app->onCreateWindow();

        mainThread->loop(app);

    } catch (const ApplicationInitException& e) {
        logError("Received an error: {} {}", e.code, e.what());
        retCode = 1;
    }

    // Release resources either if an error
    // has happened or the program has been closed
    mainThread->onDestroy();
    app->onDestroy();

    delete app;
    delete mainThread;

    logInfo("Finished with code {}", retCode);

    return retCode;
}
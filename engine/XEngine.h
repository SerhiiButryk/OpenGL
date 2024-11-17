/**
* This is a main header which defines all engine APIs
*/

#pragma once

#include "common/Log.h"
#include "Application.h"
#include "MainThread.h"
#include "common/Exception.h"

///////////////////////////////////////////////////////////////////
///////////// MAIN ENTRY POINT OF OUR PROGRAM //////////////////////
///////////////////////////////////////////////////////////////////

/**
 *  Should be implemented by client
 */
Application* getClientApplication();

int main()
{
    int retCode = 0;

    auto* app = new MainApplication();
    auto* mainThread = new MainThread();

    try {

        auto* client = getClientApplication();
        app->setClientApplication(client);

        mainThread->onCreate();

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

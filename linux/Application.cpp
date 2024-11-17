#include "XEngine.h"

class ClientApplication : public Application {
public:
    ClientApplication() = default;
    ~ClientApplication() = default;

    void onCreate() override {}
    void onDestroy() override {}
};

/**
 *  Provide a client for the engine
 */
Application* getClientApplication() {
    return new ClientApplication();
}
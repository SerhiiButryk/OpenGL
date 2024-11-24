#include "basic_tests/TestMenuUI.h"
#include "Application.h"

namespace client {
    /**
     *  Our application implementation
     */
    std::string Application::getResourcePath() { return "../../engine/res"; }

    xengine::UI* Application::createUI() { return new TestMenuUI(this); }

}

/**
*  Creates our application
*/
xengine::Application* createApplication() {
    return new client::Application();
}
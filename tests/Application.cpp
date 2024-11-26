#include "basic_tests/TestMenuUI.h"
#include "Application.h"
#include <basic_tests/BackgroundColorTest.h>

static const char* open_picker_btn_label = "Open color picker";

namespace test {
    /**
     *  Our application implementation
     */
    std::string Application::getResourcePath() { return "../../engine/res"; }

    xengine::UI* Application::createUI() {
        // Prepare test UI
        auto* test = new TestMenuUI(this);
        test->registerTest(new BackgroundColorTest(), open_picker_btn_label);

        return test;
    }

}

/**
*  Creates our application
*/
xengine::Application* createApplication() {
    return new test::Application();
}
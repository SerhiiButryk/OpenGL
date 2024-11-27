#include "Application.h"
#include <ui_tests/BackgroundColorTest.h>
#include <ui_tests/TextureTest.h>
#include <ui_tests/TestMenuUI.h>

static const char* background_color_btn_label = "Background color";
static const char* texture_btn_label = "Texture";

namespace test {
    /**
     *  Our application implementation
     */
    std::string Application::getResourcePath() { return "../../engine/res"; }

    xengine::UI* Application::createUI() {
        // Prepare test UI
        auto* test = new TestMenuUI(this);
        test->registerTest(new BackgroundColorTest(), background_color_btn_label);
        test->registerTest(new TextureTest(), texture_btn_label);

        return test;
    }

}

/**
*  Creates our application
*/
xengine::Application* createApplication() {
    return new test::Application();
}
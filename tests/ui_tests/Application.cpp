#include "Application.h"

#include <BatchingTest.h>
#include <DynamicBatching.h>
#include <ui_tests/BackgroundColorTest.h>
#include <ui_tests/TextureTest.h>
#include <ui_tests/TestMenuUI.h>

namespace test {
    /**
     *  Our application implementation
     */
    std::string Application::getResourcePath() { return "../engine/res"; }

    xengine::UI* Application::createUI() {

        const char* background_color_btn_label = "Background color";
        const char* texture_btn_label = "Texture";
        const char* batching_btn_label = "Batching";
        const char* batching_dyn_btn_label = "Dynamic batching";

        // Prepare test UI
        auto* test = new TestMenuUI(this);
        test->registerTest(new BackgroundColorTest(), background_color_btn_label);
        test->registerTest(new TextureTest(), texture_btn_label);
        test->registerTest(new BatchingTest(), batching_btn_label);
        test->registerTest(new DynamicBatching(), batching_dyn_btn_label);
        return test;
    }

}

/**
*  Creates our application
*/
xengine::Application* createApplication() {
    return new test::Application();
}
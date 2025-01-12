#include "Application.h"

#include <BatchingTest.h>
#include <ShapesTest.h>

#include <ui_tests/TextureTest.h>
#include <ui_tests/TestMenuUI.h>
#include <ui_tests/BlankTest.h>

namespace test {
    /**
     *  Our application implementation
     */
    std::string Application::getResourcePath() { return "../engine/res"; }

    xengine::UI* Application::onCreateUI() {

        const char* texture_btn_label = "Texture";
        const char* batching_btn_label = "Batching";
        const char* shapes_btn_label = "Shapes";

        // Prepare test UI
        auto* test = new TestMenuUI(this);
        test->registerTest(new TextureTest(), texture_btn_label);
        test->registerTest(new BatchingTest(), batching_btn_label);
        test->registerTest(new ShapesTest(), shapes_btn_label);

        // TODO: Uncomment for testing raw OpenGL code
        // return new BlankTest();
        return test;
    }

    xengine::WindowConfigs Application::onCreateWindow() {
        xengine::WindowConfigs config = { width, height, title };
        return config;
    }
}

/**
*  Creates our application
*/
xengine::Application* createApplication() {
    return new test::Application();
}
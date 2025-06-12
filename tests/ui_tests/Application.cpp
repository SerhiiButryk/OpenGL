#include "Application.h"

#include <ShapesTest.h>

#include <ui_tests/TextureTest.h>
#include <ui_tests/TestMenuUI.h>
#include <ui_tests/BlankTest.h>

namespace test {

    /**
     *  Client application
     */

    Application::Application() {

        const char* texture_btn_label = "Texture";
        const char* shapes_btn_label = "Shapes";

        //////////////////////////////////////////////////
        ////// Screens //////////////////////////////////
        //////////////////////////////////////////////////

        auto test = new TestMenuUI(this);
        test->registerTest(new TextureTest(this), texture_btn_label);
        test->registerTest(new ShapesComponentUI(this), shapes_btn_label);

        testMenuUI = test;
    }

    void Application::onCreate() {

        //////////////////////////////////////////////////
        ////// UI SETUP //////////////////////////////////
        //////////////////////////////////////////////////

        // TODO: Uncomment for testing raw OpenGL code
        // pushLayer(new BlankTest());
        pushLayer(static_cast<TestMenuUI*>(testMenuUI));
    }

    std::string Application::getResourcePath() { return "../engine/res"; }

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
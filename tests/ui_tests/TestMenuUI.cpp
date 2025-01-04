#include "TestMenuUI.h"

#include <imgui.h>
#include <common/Log.h>
#include <opengl/Renderer.h>

static bool testUIClosed = true;

namespace test {

    TestMenuUI::~TestMenuUI() {
        for (auto&& elem : m_tests) {
            delete elem.first;
        }
        m_tests.clear();
        LOG_INFO("TestMenuUI::~TestMenuUI");
    }

    void TestMenuUI::onCreate() {
        TestUI::onCreate();
        LOG_INFO("TestMenuUI::onCreate");
        // Call test to initialize any stuff
        for (auto&& elem : m_tests) {
            elem.first->onCreate(m_app);
        }
    }

    void TestMenuUI::onDestroy() {
        TestUI::onDestroy();
        LOG_INFO("TestMenuUI::onDestroy");
        // Call test to destroy any stuff
        for (auto&& elem : m_tests) {
            elem.first->onDestroy();
        }
    }

    void TestMenuUI::registerTest(TestCase* test, const std::string& label) {

        test->setTestUI(this);

        m_tests.push_back(std::make_pair(test, label));
    }

    /**
    * Start of render pipline
    * Define base pipline
    */
    void TestMenuUI::onDraw() {

        // Clear screen
        xengine::Renderer::clearScreen(m_color);

        // Give a chance to do something at the beginning of render process
        if (m_currentTestUI != nullptr) {
            m_currentTestUI->onBeforeRender();
        }

        // Render test UI + ImGui
        TestUI::onDraw();
    }

    /**
    * Draw ImGui here
    */
    void TestMenuUI::onRenderUI() {

        // Display Test UI
        if (m_currentTestUI != nullptr && !testUIClosed) {
            ImGui::Spacing();
            // If back button is clicked then stop rendering
            if (ImGui::Button("<--")) {
                testUIClosed = true;
                m_currentTestUI = nullptr;
                return;
            }
            // Render Test UI
            m_currentTestUI->onRender();
            return;
        }

        // Display Menu UI
        if (testUIClosed) {

            // Add button which opens a test
            for (auto&& elem : m_tests) {
                if (ImGui::Button(elem.second.c_str())) {
                    // Select test if button is clicked
                    m_currentTestUI = elem.first;
                    testUIClosed = false;
                    return;
                }
            }
        }

    }

}

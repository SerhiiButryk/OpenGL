#include "TestMenuUI.h"

#include <public/XEngine.h>

static bool testUIClosed = true;

namespace test {

    TestMenuUI::~TestMenuUI() {
        for (auto&& elem : m_tests) {
            delete elem.first;
        }
        m_tests.clear();
        LOG_INFO("TestMenuUI::~TestMenuUI");
    }

    void TestMenuUI::onAttach() {
        TestUI::onAttach();
        LOG_INFO("TestMenuUI::onAttach");
        // Call test to initialize any stuff
        for (auto&& elem : m_tests) {
            elem.first->onAttach();
        }
    }

    void TestMenuUI::onDetach() {
        TestUI::onDetach();
        LOG_INFO("TestMenuUI::onDetach");
        // Call test to destroy all stuff
        for (auto&& elem : m_tests) {
            elem.first->onDetach();
        }
    }

    void TestMenuUI::registerTest(TestCase* test, const std::string& label) {

        test->setTestUI(this);

        m_tests.emplace_back(test, label);
    }

    /**
    * Start of render pipline
    * Define base pipline
    */
    void TestMenuUI::onDraw() {

        // Clear screen
        xengine::Renderer::clearScreen({m_color[0], m_color[1], m_color[2], m_color[3]});

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
            m_currentTestUI->onDraw();
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

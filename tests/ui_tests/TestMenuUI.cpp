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
        LOG_INFO("TestMenuUI::onAttach");
        // Call test to initialize any stuff
        for (auto&& elem : m_tests) {
            elem.first->onAttach();
        }
    }

    void TestMenuUI::onDetach() {
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

    void TestMenuUI::onDraw() {
        // Render test shapes
        if (m_currentTestUI != nullptr && !testUIClosed) {
            m_currentTestUI->onDraw();
        }
    }

    void TestMenuUI::onDrawUI() {

        ImGui::Begin("Tests");

        ImGui::Spacing();

        // Add test UI
        if (m_currentTestUI != nullptr && !testUIClosed) {
            ImGui::Spacing();
            // If back button is clicked then stop rendering
            if (ImGui::Button("<-")) {
                testUIClosed = true;
                m_currentTestUI = nullptr;
            } else {
                // Render Test UI
                m_currentTestUI->onDrawUI();
            }
        }

        // Add a bunch of buttons
        if (testUIClosed) {
            // Add button which opens a test
            for (auto&& elem : m_tests) {
                if (ImGui::Button(elem.second.c_str())) {
                    // Select test if button is clicked
                    m_currentTestUI = elem.first;
                    testUIClosed = false;
                }
            }
        }

        ImGui::End();
    }

}

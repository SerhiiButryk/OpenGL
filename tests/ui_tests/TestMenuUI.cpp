#include "TestMenuUI.h"

#include <imgui.h>
#include <common/Log.h>

static bool testUIClosed = true;

namespace test {

    TestMenuUI::~TestMenuUI() {
        for (auto&& elem : m_tests) {
            delete elem.first;
        }
        m_tests.clear();
        logInfo("TestMenuUI::~TestMenuUI");
    }

    void TestMenuUI::onCreate() {
        TestUI::onCreate();
        logInfo("TestMenuUI::onCreate");
        // Call test to initialize any stuff
        for (auto&& elem : m_tests) {
            elem.first->onCreate(m_app);
        }
    }

    // Repeatedly called by the MainThread
    void TestMenuUI::onRenderUI() {

        // Display Test UI
        if (m_currentTestUI != nullptr && !testUIClosed) {
            ImGui::Spacing();
            // If back button is clicked then stop rendering
            if (ImGui::Button("<--")) {
                testUIClosed = true;
                return;
            }
            // Render Test UI
            m_currentTestUI->onRender();
            return;
        }

        // Display Menu UI
        if (testUIClosed) {
            for (auto&& elem : m_tests) {
                // Add button for every test
                if (ImGui::Button(elem.second.c_str())) {
                    // Select test if button is clicked
                    m_currentTestUI = elem.first;
                    testUIClosed = false;
                    return;
                }
            }
        }

    }

    void TestMenuUI::onRender() {
        // Give a chance to first call a test render
        for (auto&& elem : m_tests) {
            elem.first->onBeforeRender();
        }
        // Render all other UI stuff
        TestUI::onRender();
    }

    void TestMenuUI::onDestroy() {
        TestUI::onDestroy();
        logInfo("TestMenuUI::onDestroy");
        // Call test to destroy any stuff
        for (auto&& elem : m_tests) {
            elem.first->onDestroy();
        }
    }

    void TestMenuUI::registerTest(TestCase* test, const std::string& label) {
        m_tests.push_back(std::make_pair(test, label));
    }

}

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
            elem.first->onCreate();
        }
    }

    void TestMenuUI::onRenderUI() {

        // Render Test UI
        for (auto&& elem : m_tests) {

            // Show current Test UI
            if (m_currentTestUI != nullptr && !testUIClosed) {
                if (ImGui::Button("<--")) {
                    testUIClosed = true;
                }
                m_currentTestUI->onRenderUI();
            }

            // Show Menu UI
            if (testUIClosed) {
                if (ImGui::Button(elem.second.c_str())) {
                    m_currentTestUI = elem.first;
                    testUIClosed = false;
                }
            }

        }
    }

    void TestMenuUI::onRender() {
        // Give a chance to make changes for the test
        for (auto&& elem : m_tests) {
            elem.first->onRender();
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

    void TestMenuUI::registerTest(TestUI* test, const std::string& label) {
        m_tests.push_back(std::make_pair(test, label));
    }

}

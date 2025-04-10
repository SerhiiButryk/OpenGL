#pragma once

#include <vector>

#include "base/TestCase.h"
#include "base/TestUI.h"

namespace test {

    class TestMenuUI : public TestUI {
    public:
        explicit TestMenuUI(Application* app) : TestUI(app) {}
        ~TestMenuUI() override;

        void onAttach() override;
        void onDraw() override;
        void onDetach() override;

        // Should be called to create ImGui UI
        void onRenderUI() override;

        void registerTest(TestCase*, const std::string&);

    private:
        // A test + button label collection
        std::vector<std::pair<TestCase*, std::string>> m_tests;
        // Current text UI
        TestCase* m_currentTestUI = nullptr;
    };

}

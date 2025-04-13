#pragma once

#include <vector>

#include "base/TestCase.h"

namespace test {

    class TestMenuUI : public xengine::UIComponent {
    public:
        explicit TestMenuUI(Application* app) : m_app(app) {}
        ~TestMenuUI() override;

        void onAttach() override;
        void onDetach() override;

        void onDraw() override;
        void onDrawUI() override;

        void registerTest(TestCase*, const std::string&);

    private:
        // A test + button label collection
        std::vector<std::pair<TestCase*, std::string>> m_tests;
        // Current text UI
        TestCase* m_currentTestUI = nullptr;
        Application* m_app = nullptr;
    };

}

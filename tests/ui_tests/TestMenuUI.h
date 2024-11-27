#pragma once

#include <vector>

#include "base/TestCase.h"
#include "base/TestUI.h"

namespace test {

    class TestMenuUI : public TestUI {
    public:
        explicit TestMenuUI(Application* app) : TestUI(app) {}
        ~TestMenuUI() override;

        void onCreate() override;
        void onRender() override;
        void onDestroy() override;
        void onRenderUI() override;

        void registerTest(TestCase*, const std::string&);

    private:
        // A test + button label collection
        std::vector<std::pair<TestCase*, std::string>> m_tests;
        // Current text UI
        TestCase* m_currentTestUI = nullptr;
    };

}

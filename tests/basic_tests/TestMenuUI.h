#pragma once

#include <vector>

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

        void registerTest(TestUI*, const std::string&);

    private:
        // A test + button label collection
        std::vector<std::pair<TestUI*, std::string>> m_tests;
        // Current text UI
        TestUI* m_currentTestUI = nullptr;
    };

}

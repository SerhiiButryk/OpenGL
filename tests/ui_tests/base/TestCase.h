#pragma once

#include <Application.h>

namespace test {

    class TestCase
    {
    public:
        explicit TestCase(Application* app) { m_app = app; };
        virtual ~TestCase() = default;

        virtual void onCreate(Application* app) {}
        virtual void onBeforeRender() {}
        virtual void onDestroy() {}
        virtual void onRender() {}

        void setTestUI(void* ptr) { testUI = ptr; }
        void* getTestUI() { return testUI; }

    private:
        void* testUI = nullptr;

    protected:
        Application* m_app = nullptr;
    };

}

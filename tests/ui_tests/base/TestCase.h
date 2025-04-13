#pragma once

#include <Application.h>

namespace test {

    class TestCase
    {
    public:
        explicit TestCase(Application* app) { m_app = app; }
        virtual ~TestCase() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}

        virtual void onDraw() {}
        virtual void onDrawUI() {}

        void setTestUI(void* ptr) { m_testUI = ptr; }
        void* getTestUI() { return m_testUI; }

    private:
        void* m_testUI = nullptr;

    protected:
        Application* m_app = nullptr;
    };

}

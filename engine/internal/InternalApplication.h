#pragma once

#include <window/Window.h>

namespace xengine {

    /**
    * Our internal application class which we use inside engine.
    * Expose only an interface for client side.
    */
    class InternalApplication : public MainThreadObserver {
    public:
        InternalApplication() : m_parentWindow(new Window()) {}
        ~InternalApplication() override {
            delete m_parentWindow;
        }

        void onCreate() override {}
        void onDestroy() override {}

        void* getWindow() const { return m_parentWindow->getWindow(); }

    protected:
        Window* m_parentWindow = nullptr;
    };

}

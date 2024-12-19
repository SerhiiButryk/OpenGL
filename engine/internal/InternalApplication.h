#pragma once

#include <window/Window.h>
#include "Lifecycle.h"

namespace xengine {

    /**
    * Our Internal application class which we use inside engine.
    * We control it and do not expose it to the client code.
    */
    class InternalApplication : public Lifecycle {
    public:
        InternalApplication() : m_parentWindow(new Window()) {}
        ~InternalApplication() override {
            delete m_parentWindow;
        };

        void onCreate() override {}
        void onDestroy() override {}

        void* getWindow() const { return m_parentWindow->getWindow(); }

    protected:
        Window* m_parentWindow = nullptr;
    };

}

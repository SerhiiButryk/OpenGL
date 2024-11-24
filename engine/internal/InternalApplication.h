#pragma once

#include <window/Window.h>
#include "Lifecycle.h"

namespace xengine {
    /**
    * Internal application class
    */
    class InternalApplication : public Lifecycle {
    public:
        InternalApplication() : m_parentWindow(new Window()) {}
        ~InternalApplication() override = default;

        void onCreate() override {}
        void onDestroy() override {}

        void* getWindow() const { return m_parentWindow->getWindow(); }

    protected:
        Window* m_parentWindow = nullptr;
    };

}

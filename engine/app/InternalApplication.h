#pragma once

#include <common/Timestamp.h>
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

        auto getWindow() const { return m_parentWindow->getWindow(); }

        auto getFrameDeltaTime() const { return m_frameDeltaTime; }
        void setFrameDeltaTime(Timestamp timestamp) { m_frameDeltaTime = timestamp; }

    protected:
        Window* m_parentWindow = nullptr;
        Timestamp m_frameDeltaTime = 0.0f;
    };

}

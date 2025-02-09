#pragma once

#include <common/Timestamp.h>
#include <window/Window.h>
#include <component/LayerStack.h>

namespace xengine {

    /**
    * Internal application class which is an implementation detail of the engine.
    * Exposed only as an interface.
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

        // ------------------------------------
        // UI layer APIs
        // ------------------------------------

        virtual void pushLayer(Layer *layer) = 0;
        virtual void popLayer(Layer *layer) = 0;
        virtual void pushOverLayer(Layer *layer) = 0;
        virtual void popOverLayer(Layer *layer) = 0;

    protected:
        Window* m_parentWindow = nullptr;
        Timestamp m_frameDeltaTime = 0.0f;
    };

}

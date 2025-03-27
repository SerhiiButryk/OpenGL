#pragma once

#include <ui/DecoratorUI.h>
#include <MainThread.h>
#include <app/Application.h>

namespace xengine {

    /*
     * A class which represents an instance of our application.
     * An application manages only high level states or configurations, like a window.
     */
    class MainApplication final : public InternalApplication,
        public EventListener, public Lifecycle
    {
    public:
        MainApplication();
        ~MainApplication() override;

        /////////////////////////////////
        // Thread lifecycle callbacks
        /////////////////////////////////

        void onCreate() override;
        void onDestroy() override;

        /////////////////////////////////
        // Thread state callbacks
        /////////////////////////////////

        void onStart() override;

        void onProcess(void *app) override;

        void onEnd() override;

        void setClientApplication(Application* app) {
            m_clientApp = app;
        }

        auto getClientApplication() const { return m_clientApp; }

        void attachThread(MainThread* mainThread);

#ifdef UNIT_TESTS
        void* getParentWindowForTest() const { return m_parentWindow; }
#endif

        // ------------------------------------
        // Events from the system or window
        // ------------------------------------
        bool onEvent(const Event &event) override;

        // ------------------------------------
        // UI layer APIs
        // ------------------------------------

        void pushLayer(Layer *layer) override;
        void popLayer(Layer *layer) override;
        void pushOverLayer(Layer *layer) override;
        void popOverLayer(Layer *layer) override;

    private:
        Application* m_clientApp = nullptr;
        DecoratorUI* m_decoratorUI = nullptr;
        MainThread* m_main_thread = nullptr;
        // Layer stack manages UI layers of our application
        // It could be a client UI layers or our own UI layers
        LayerStack m_layerStack;
    };

}

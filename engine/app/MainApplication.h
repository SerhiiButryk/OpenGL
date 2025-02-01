#pragma once

#include <ui/AppUI.h>
#include <MainThread.h>
#include <app/Application.h>

namespace xengine {

    /*
     * A class which represents an instance of our application.
     * An application manages only high level states or configurations, like a window.
     */
    class MainApplication final : public InternalApplication, public EventListener {
    public:
        MainApplication();
        ~MainApplication() override;

        void onCreateWindow() const;

        /////////////////////////////////
        // Thread lifecycle callbacks
        /////////////////////////////////

        void onCreate() override;
        void onDestroy() override;

        /////////////////////////////////
        // Thread while loop callbacks
        /////////////////////////////////

        void onStart() override;

        void onProcess(void *app) override;

        void onEnd() override;

        void setClientApplication(Application* app) {
            m_clientApp = app;
            m_appUI->setClientApp(m_clientApp);
        }

        auto getClientApplication() const { return m_clientApp; }

        void attachThread(MainThread* mainThread);

#ifdef UNIT_TESTS
        void* getParentWindowForTest() const { return m_parentWindow; }
        UI* getClientUI() const { return m_appUI->getClientUI(); }
#endif

        // ------------------------------------
        // Events from application or window
        // ------------------------------------
        bool onEvent(const Event &event) override;

    private:
        Application* m_clientApp = nullptr;
        ApplicationUI* m_appUI = nullptr;
        MainThread* m_main_thread = nullptr;
    };

}

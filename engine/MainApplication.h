#pragma once

#include <ui/AppUI.h>
#include "MainThread.h"
#include "internal/Application.h"

namespace xengine {

    /*
     * A class which represents an instance of our application.
     * An application manages only high level states or configurations, like a window.
     */
    class MainApplication : public InternalApplication, public EventListener{
    public:
        MainApplication();
        ~MainApplication() override;

        void onCreateWindow() const;

        void onCreate() override;
        void onDestroy() override;

        inline void setClientApplication(Application* app) { m_clientApp = app; }
        inline Application* getClientApplication() const { return m_clientApp; }

        void attachThread(MainThread* mainThread);

        inline void setClientUI(UI* clientUI) {  m_appUI->setClientUI(clientUI); }

#ifdef UNIT_TESTS
        void* getParentWindowForTest() const { return m_parentWindow; }
        UI* getClientUI() const { return m_appUI->getClientUI(); }
#endif

        // Events
        bool onEvent(const Event &event) override;

    private:
        Application* m_clientApp = nullptr;
        ApplicationUI* m_appUI = nullptr;
        MainThread* m_main_thread = nullptr;
    };

}

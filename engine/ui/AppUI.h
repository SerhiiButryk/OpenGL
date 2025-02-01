#pragma once

#include <app/Application.h>
#include <ui/UI.h>
#include <MainThreadObserver.h>

namespace xengine {

    /**
    * Application UI component.
    *
    * This is a part which manages and knows about our client UI.
    */
    class ApplicationUI : public MainThreadObserver
    {
    public:
        explicit ApplicationUI();
        ~ApplicationUI() override;

        void onProcess(void* app) override;

        void onCreate() override;
        void onDestroy() override;

        void setClientApp(Application* app) { m_clientApp = app; }

#ifdef UNIT_TESTS
        UI* getClientUI() const { return m_clientUI; }
#endif

    private:
        Application* m_clientApp = nullptr;
        UI* m_clientUI = nullptr;
    };
}
